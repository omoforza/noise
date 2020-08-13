//22.09.2016 ricontrollo di aver cambiato ovunque il parametro tempo con il tempo NON incrementale

//ho corretto manualmente omega0

//attenzione ad ever ritardato l'accensione degli integratori successivi allo stadio C

//controllare il rumore in lunghezza ed in frequenza

//controllare la proporzionalità tra il segnale del servo e lo shift in frequenza

//verificare che il calcolo della fase sia completo , non rilassamento

//verificare che avvenga la correzione di omega

//attenzione al filtro passa alto prima dopo il fotodiodo

#include<iostream>
#include<random>
#include<fstream>
#include<cmath>
#include<complex>
#include<fftw3.h> 

using namespace std;

//********** passa alto - dopo il fotodiodo ********************************

long double hpf(long double Iin,long double R,long double L, long double Vold, long double Iold, long double dt)
{
return (Vold + R*(Iin - Iold))/(1.0L + dt*R/L )/R;  //R finale è per normalizzare
}

//********** risposta attuatore piezoelettrico ****************************

long double apz(long double vpzold,long double cf,long double rf,long double r1,long double vin,long double dt)
{
long double tf = 1.0L/((1.0L/r1+1.0L/rf)/cf);  
return (vpzold + dt*vin/cf/rf)/(1.0L+dt/tf);
}

//********** blocco A ******************************************************

long double bloccoA(long double R1, long double C1 , long double Vin, long double Vout_old, long double dt)
{return (Vout_old + (dt/C1)/R1*Vin)/(1.0L+(dt/C1)/R1);}

//********** blocco B ******************************************************

long double amp_inv(long double R1,long double R2,long double R,long double Rout,long double Cout,long double dt,long double Vin ,long double Vout_old,long double G){

const long double     a = -1.0L -G*R1/(R1+R2)-R/R2+R/R2*R1/(R1+R2)-R/Rout ;
const long double     b = -G*R2/(R1+R2)+R/(R1+R2) ;
const long double theta = R*Cout ;

return (Vout_old + dt*b/theta*Vin)/(1.0L-dt*a/theta);
}

long double amp_invID(long double R1,long double R2,long double Vin)
{return -R2/R1*Vin;}

//********** blocco int ******************************************************

long double integratore1(long double R1,long double R2,long double R,long double Rout,long double Cout,long double C1,long double dt,long double Vin,long double Vin_old,long double V_old,long double Vout_old, long double G){

long double A     = (-1.0L-R/Rout)/R/Cout ;
long double B     = (-G-R/R1)/R/Cout ;
long double theta = 1.0L/R1/Cout;

return (Vout_old*(1.0L-(1.0L+R2/R1)/dt/B-1.0L/C1/R1/B)
+Vin*(-theta/B*(1.0L+R2/R1)-R2/R1-dt/C1/R1-theta/B*dt/C1/R1)
-V_old*(1.0L+R2/R1)
+Vin_old*(R2/R1))
/
(1.0L-(1.0L+R2/R1)*(1.0L-dt*A)/dt/B-(1.0L-dt*A)/B/C1/R1);
}


long double integratore2(long double R1,long double R2,long double R,long double Rout,long double Cout,long double C1,long double dt,long double Vin,long double Vin_old,long double V_old,long double Vout_old,long double Vout, long double G){

long double A     = (-1.0L-R/Rout)/R/Cout ;
long double B     = (-G-R/R1)/R/Cout ;
long double theta = 1.0L/R1/Cout;

return Vout*(1.0L-dt*A)/dt/B-Vout_old/dt/B-theta/B*Vin;
}

long double integratoreID(long double R1,long double R2,long double C1,long double dt,long double Vin,long double Vin_old,long double Vout_old)
{return Vout_old - R2/R1*(Vin - Vin_old) - Vin/R1*(dt/C1);}

//********** blocco F1 ******************************************************

long double bloccoF1(long double R1,long double R2,long double R3,long double R,long double Rout,long double Cout,long double C1,long double dt,long double Vin,long double Vin_old,long double V_old,long double Vout_old,long double G){

long double        a = (1.0L/R+1.0L/Rout)/Cout;
long double        S = -1.0L/Cout*(1.0L/R1+G/R); 
long double    theta = 1.0L/(R1*Cout);
long double    alpha = 1.0L/R1+R2/R1/R3;
long double    gamma = C1*(R2/R1);
long double    beta1 = 1.0L/R1+(R1+R2)/R1/R3;
long double    delta = C1/R1*(R1+R2);

return (Vout_old*(1.0L-beta1/(C1*S)-delta/(C1*dt*S))
-Vin*(delta*theta/(C1*S)+dt*beta1*theta/(C1*S)+gamma/C1+dt*(alpha/C1))
-delta/C1*V_old
+gamma/C1*Vin_old
)/(1.0L
-delta/(C1*dt*S)*(1.0L+dt*a)
+dt/(R3*C1)
-beta1/(C1*S)*(1.0L+dt*a)
);
}

long double bloccoF2(long double R1,long double R2,long double R3,long double R,long double Rout,long double Cout,long double C1,long double dt,long double Vin,long double Vin_old,long double V_old,long double Vout_old,long double Vout,long double G){

long double        a = (1.0L/R+1.0L/Rout)/Cout;
long double        S = -1.0L/Cout*(1.0L/R1+G/R); 
long double    theta = 1.0L/(R1*Cout);

return Vout*(1.0L+dt*a)/(dt*S)-Vout_old/(dt*S)-(theta/S)*Vin;
}

long double bloccoFID(long double R1,long double R2,long double R3,long double C1,long double dt,long double Vin,long double Vin_old,long double Vout_old){

return (Vout_old-R2/R1*(Vin-Vin_old)-(R2+R3)/(R1*R3)*Vin*(dt/C1))/(1.0L+(dt/C1)/R3);
}

//********** blocco H ******************************************************
long double bloccoH(long double R1, long double C1, long double Vin, long double Vout_old, long double dt)
{return Vout_old - (dt/C1)/R1*Vin;}

long double bloccoH1(long double R1, long double C1, long double Vin, long double Vout_old, long double dt, long double V_old,long double G,long double Rout,long double Cout,long double R)
{
long double A    = -G/R/(C1+Cout);
long double B    = C1/(C1+Cout);
long double C    = -(Rout+R)/(Rout*R)/(C1+Cout);
long double chi  = (B+dt*A)/(1.0L+dt/(R1*C1));

return ((1.0L-chi)*Vout_old + (chi-B)*V_old+chi*dt/R1/C1*Vin)/(1.0L-dt*C-chi);
}

long double bloccoH2(long double R1, long double C1, long double Vin, long double Vout_old, long double dt, long double V_old,long double G,long double Rout,long double Cout,long double R, long double Vout)
{
return (Vout-Vout_old+V_old+dt/R1/C1*Vin)/(1.0L+dt/(R1*C1));
}

int main()
{
cout.precision(15);

//************* CARATTERISTICHE CAVITA' - DICHIARAZIONE COSTANTI************



const unsigned int       Ncamp = 5000000 ; //ben funziona anche con 5M
const long double           L0 = 0.885L;                     
const long double            c = 299792458.0L ;
const long double          FSR = c/(2.0L*L0) ;
const long double       kboltz = 1.3806488e-23L ;            
const long double           PI = acosl(-1.0L) ; 
const long double        freq0 = FSR*1663532.0L;
const long double       omega0 = 2.0L*PI*freq0;
const long double         temp = 300.0L ;
const complex<long double>  ta = {sqrt(1.0L-0.99826L),0.0L} ;
const complex<long double>  ra = {sqrt(0.99826L),0.0L} ;
const complex<long double>  rb = {sqrt(0.99826L),0.0L} ;
const long double           Ra = pow(abs(ra),2.0L) ;
const long double           Rb = pow(abs(rb),2.0L) ;
const complex<long double> IMM = -1.0L ;
const complex<long double>  im = sqrt(IMM) ;
const long double            finesse = PI*pow(Ra*Rb,0.25L)/(1.0L-sqrt(Ra*Rb)) ;
const long double     larghezza_riga = FSR/finesse; 

//variazione lunghezza rispetto L0 nel tempo
long double*                       dL = new long double[Ncamp];
*dL = {};
dL[0] = 0.0L;
long double*                       dLf = new long double[Ncamp];
*dLf = {};
dLf[0] = 0.0L;
 
//************** GENERATORE NUMERI CASUALI *********************************

default_random_engine              generator(84743367);
normal_distribution<long double>   normal(0.0L,1.0L);

//************** INTERVALLO TEMPORALE ***************************************

long double*           deltaT2 = new long double[Ncamp]; 
long double*             tempo = new long double[Ncamp]; //problemi di precisione macchina (aaa)
long double*             res_t = new long double[Ncamp];
long double            deltaX1 = 0.0L; 
long double            deltaX2 = 0.0L;
long double             sigmaL = 0.0L; //varianza spostamento specchi


*deltaT2 = {};
*tempo   = {};
*res_t   = {};

res_t[0]   = 0.0L;
deltaT2[0] = 2.0L*L0/c;

//************* PARAMETRI CAMPO INCIDENTE E MODULAZIONE *********************
const long double               beta = 1.1L ;    //di default uso 1.1L
const long double              freqM = 717.7e3L; //50000.0L*larghezza_riga/2.0L/PI ; //di solito 10000 
const long double             omegaM = 2.0L*PI*freqM;
long double *                  omega = new long double[Ncamp];
long double *                 domega = new long double[Ncamp]; //variazione di omega ad ogni ciclo
long double *                    phi = new long double[Ncamp]; 
complex<long double> *          Einc = new complex<long double>[Ncamp];
complex<long double>            Ainc = {sqrt(40.0e-3L),0.0L}; //lo scelgo così da avere l'intensità \approx 40mW

*omega        = {};
*domega       = {};
*Einc         = {};
*phi          = {};
omega[0]      = omega0;
omega[1]      = omega0;

//************* PARAMETRI ATTUATORE PIEZOELETTRICO *************************

long double*    Vpz = new long double[Ncamp]; //segnale in Hz di modifica di omega in uscita dal piezo
*Vpz   = {};
Vpz[0] = 0.0L;

long double Rpzf = 100.0L;
long double Rpz1 = 100.0L;
long double Cpzf = 8.0e-8L; //capacità in fahrad del circuito equivalente del piezo

//************* PARAMETRI FILTRO PASSA ALTO ********************************

long double*    Vhp = new long double[Ncamp];
*Vhp   = {};
Vhp[0] = 0.0L;

long double Lhp  = 30.0e-3L;   //henry
long double Rhp  = 10.0e3L  ;   //ohm modificato il 22.09.2016 da 5e3 a 10e3

//************* PARAMETRI CAMPO INTERNO E RIFLESSO *************************

complex<long double>*    Eplus = new complex<long double>[Ncamp];
complex<long double>*    Erifl = new complex<long double>[Ncamp];


*Erifl   = {};
*Eplus   = {};
tempo[0] = 0.0L;
phi  [0] = 0.0L;
Einc [0] = Ainc;
Eplus[0] =  ta*Einc[0];
Erifl[0] = -ra*Einc[0];

//************* PARAMETRI INTENSITÀ RIFLESSA *******************************

long double *            Irifl = new long double[Ncamp];


*Irifl   = {};
Irifl[0] = real(Erifl[0]*conj(Erifl[0])); //rivedo definizione

//************* PARAMETRI FUNZIONE D'ERRORE E MIXER ************************

long double *  error_func_fast = new long double[Ncamp];
long double *  error_func_slow = new long double[Ncamp];
long double *       mixed_sign = new long double[Ncamp];
long double *           demod  = new long double[Ncamp];
long double          mix_phase = -PI/2.0L; //-PI/2 default


*demod             = {} ;
demod[0]           = 0.0L;
*error_func_fast   = {}  ;
*error_func_slow   = {}  ;
error_func_fast[0] = 0.0L ; 
error_func_slow[0] = 0.0L ; 
*mixed_sign        = {}  ;
mixed_sign[0]      = 0.0L ; 

//************* PARAMETRI FOTODIODO **************************************

long double        cor_foto = 0.0L;
long double    cor_foto_old = 0.0L;

long double        preamp   = 0.0L;
long double     preampold   = 0.0L;

const long double      bs   = 0.035L;    

//************* PARAMETRI ELETTRONICA **************************************

//parametri di rumore op-amp

long double   G = 600.0e3L; //tutte le prove fatte con G = 600.0e3

//**************************************************************************

long double ENB = 150.1e3;
long double  in = 1.0e-14;
long double  vn = 12.0e-9;
long double fnc = 100.0;
long double  fh = 150.1e3;
long double  fl = 0.01;

//*** A ********************************************************************

long double *  Vin_A       =  new long double[Ncamp];
long double * Vout_A       =  new long double[Ncamp];
long double * V_A          =  new long double[Ncamp];

*Vout_A  = {};
*Vin_A   = {};
*V_A     = {};

Vout_A [0] = 0.0L;
Vin_A  [0] = 0.0L;
V_A    [0] = 0.0L;

const long double     R1_A = 1.0e3L;
const long double     C1_A = 9.0e-9L; 
const long double      R_A = 0.5L;
const long double   Cout_A = 3.0e-12L;
const long double   Rout_A = 390.0L;

//*** B ********************************************************************

long double *  Vin_B       =  new long double[Ncamp];
long double * Vout_B       =  new long double[Ncamp];
long double * Voutn_B      =  new long double[Ncamp];

*Vout_B  = {};
*Voutn_B = {};
*Vin_B   = {};

Vout_B [0] = 0.0L;
Voutn_B[0] = 0.0L;
Vin_B  [0] = 0.0L;

const long double     R1_B = 333.0L;
const long double     R2_B = 6.7e3L;
const long double   Rout_B = 4.7e3L;
const long double      R_B = 0.5L;
const long double   Cout_B = 3.0e-12L; 
const long double     R3_B = 50.0L;

//*** C ********************************************************************

long double * Vin_C        =  new long double[Ncamp];
long double * Vout_C       =  new long double[Ncamp];
long double * Voutn_C      =  new long double[Ncamp];
long double * Vc_C         =  new long double[Ncamp];

*Vout_C  = {};
*Voutn_C = {};
*Vin_C   = {};
*Vc_C    = {};

Vout_C [0] = 0.0L;
Voutn_C[0] = 0.0L;
Vin_C  [0] = 0.0L;
Vc_C   [0] = 0.0L;

const long double   Rout_C = 4.7e3L;
const long double      R_C = 0.5L;
const long double   Cout_C = 3.0e-12L; 

const long double     R1_C = 4.7e3L;
const long double     R2_C = 4.7e3L;
const long double     R3_C = 50.0L;
const long double     C1_C = 5.6e-9L;

//*** D ********************************************************************

long double *  Vin_D       =  new long double[Ncamp];
long double * Vout_D       =  new long double[Ncamp];
long double * Voutn_D      =  new long double[Ncamp];
long double * Vc_D         =  new long double[Ncamp];

*Vout_D  = {};
*Voutn_D = {};
*Vin_D   = {};
*Vc_D   =  {};

Vout_D [0] = 0.0L;
Voutn_D[0] = 0.0L;
Vin_D  [0] = 0.0L;
Vc_D   [0] = 0.0L;

const long double     R1_D = 4.7e3L;
const long double     R2_D = 4.7e3L;
const long double   Rout_D = 22.0e3L;
const long double      R_D = 0.5L;
const long double   Cout_D = 3.0e-12L; 
const long double     R3_D = 50.0L;
const long double     C1_D = 5.6e-9L; 

//*** E ********************************************************************

long double *  Vin_E       =  new long double[Ncamp];
long double * Vout_E       =  new long double[Ncamp];
long double * Voutn_E      =  new long double[Ncamp];
long double * Vc_E         =  new long double[Ncamp];

*Vout_E  = {};
*Voutn_E = {};
*Vin_E   = {};
*Vc_E    = {};

Vout_E [0] = 0.0L;
Voutn_E[0] = 0.0L;
Vin_E  [0] = 0.0L;
Vc_E   [0] = 0.0L;

const long double     R1_E = 22.0e3L;
const long double     R2_E = 22.0e3L;
const long double   Rout_E = 1.0L/(1.0L/4.7e3L+1.0L/1.0e6L);
const long double      R_E = 0.5L;
const long double   Cout_E = 3.0e-12L; 
const long double     R3_E = 50.0L;
const long double     C1_E = 1.2e-9L;

//**********************************  F  *************************************

long double * Vin_F        =  new long double[Ncamp];
long double * Vout_F       =  new long double[Ncamp];
long double * Voutn_F      =  new long double[Ncamp];
long double * Vc_F         =  new long double[Ncamp];


*Vout_F  = {};
*Voutn_F = {};
*Vin_F   = {};
*Vc_F    = {};

Vout_F [0] = 0.0L;
Voutn_F[0] = 0.0L;
Vin_F  [0] = 0.0L;
Vc_F   [0] = 0.0L;

const long double     R1_F = 4.7e3L;
const long double     R2_F = 5.6L; 
const long double     R3_F = 1.0e6L;
const long double     R4_F = 50.0L;
const long double     C1_F = 1.0e-6L;

const long double      R_F = 0.5L;

const long double   Rout_F = 1000.0L;
const long double   Cout_F = 3.0e-12L; 

//*** G ********************************************************************

long double *  Vin_G       =  new long double[Ncamp];
long double * Vout_G       =  new long double[Ncamp];
long double * Voutn_G      =  new long double[Ncamp];

*Vout_G  = {};
*Voutn_G = {};
*Vin_G   = {};

Vout_G [0] = 0.0L;
Voutn_G[0] = 0.0L;
Vin_G  [0] = 0.0L;

const long double     R1_G = 1000.0L;
const long double     R2_G = 1000.0L;
const long double   Rout_G = 4.7e3L; 
const long double      R_G = 0.5L;
const long double   Cout_G = 3.0e-12L;
const long double     R3_G = 50.0L;

//*** H ********************************************************************

long double *   Vin_H       =  new long double[Ncamp];
long double *  Vout_H       =  new long double[Ncamp];
long double *     V_H       =  new long double[Ncamp];
long double * Voutn_H       =  new long double[Ncamp];

*Vout_H  = {};
*Voutn_H = {};
*Vin_H   = {};
*V_H     = {};

Vout_H [0] = 0.0L;
Voutn_H[0] = 0.0L;
Vin_H  [0] = 0.0L;
V_H    [0] = 0.0L;

const long double   Rout_H = 1.0e6L;
const long double      R_H = 0.5L;
const long double   Cout_H = 3.0e-12L; 

const long double     R1_H = 1.0e6L;
const long double     R3_H = 50.0L;
const long double     C1_H = 1.0e-6L;

//*** I ********************************************************************

long double *  Vin_I       =  new long double[Ncamp];
long double * Vout_I       =  new long double[Ncamp];
long double * Voutn_I      =  new long double[Ncamp];

*Vout_I  = {};
*Voutn_I = {};
*Vin_I   = {};

Vout_I [0] = 0.0L;
Voutn_I[0] = 0.0L;
Vin_I  [0] = 0.0L;

const long double     R1_I = 1.0e6L;
const long double     R2_I = 1.0e6L;
const long double   Rout_I = 33.0e3L;
const long double      R_I = 0.5L;
const long double   Cout_I = 3.0e-12L; 
const long double     R3_I = 50.0L;

//************* INIZIO DEL GRANDE CICLO DEL PROGRAMMA **********************

for(int i = 1; i < Ncamp-1; i++)
{

//********** valuto la posizione degli specchi *****************************

deltaX1       = 0.0L;//1.0e-8*normal(generator)   ;
deltaX2       = 0.0L;//1.0e-8*normal(generator)   ;
//if(i == 2500000){deltaX2 = 0.8e-7L;};//spike in lunghezza

// aggiungo filtro passa basso che tagli a circa 1MHz

dL[i]  = dL[i-1] + (deltaX2 - deltaX1);
dLf[i] = bloccoA( 10000.0L,1.0e-9L ,dL[i], dLf[i-1], deltaT2[i-1]) ; //dL filtrato

//********** valuto l'intervallo temporale *********************************

deltaT2[i]    = 2.0L*L0/c ; //tengo conto separatamente del rumore in lunghezza (ha senso???aaa)

res_t[i]      = res_t[i-1] + 2.0L*dLf[i]/c;

tempo[i]      = tempo[i-1] + deltaT2[i] ;

//********** azione del segnale d'errore ***********************************

domega[i] = 1.0e12L*error_func_fast[i-1];    //1.0e12 usato sempre nei test

omega[i] = omega[i-1] + domega[i];

//omega[i] = omega[i] + 0.01L*normal(generator)         ;//drift in frequenza medio 14kHz/s

//if(i == 500000){omega[i] = omega[i] + 2.0L*PI*5.0L;} //spike

// rampa:: per usare la rampa devo disattivare la correzione alla frequenza angolare. 
//commentandola fuori dal programma e lasciando solamente:: omega[i] = omega[i-1];

/*
domega[i] = 0.0L;
if(i == 1 )
{omega[i] = omega0 - 1.25e7L; } // fatto per Ncamp = 5M
if(i >= 1)
{
omega[i] = omega[i] + 2.0L*PI*0.4L;
}
//fine rampa*/

// rampa per intensità:: per usare la rampa devo disattivare la correzione alla frequenza angolare. 
//commentandola fuori dal programma e lasciando solamente:: omega[i] = omega[i-1];

/*
domega[i] = 0.0L;
if(i == 1 )
{omega[i] = omega0 - 3.2e6L;} // fatto per Ncamp = 5M
if(i >= 1)
{
omega[i] = omega[i] + 2.0L*PI*150.0L;  //normalmente 0.1L
}
//fine rampa*/
//********** valuto la fase ************************************************

//phi[i]        = omega[i]*tempo[i];// + beta*sinl(omegaM*tempo[i]) ; //fase non approssimata con t[i] che mi da problemi

//fase approssimata 1 (vedi appunti)

//phi[i]        = omega[i-1]*deltaT2[0]*(long double)i;//ricorda il punto e virgola!!!!
            /*  + domega[i]*deltaT2[0]+ domega[i]*deltaT2[0]*(long double)(i-1)
              + omega[i-1]* 2.0L*dLf[i]/c + domega[i] * 2.0L*(dLf[i])/c
              + beta*sinl(omegaM*deltaT2[0]*(long double)(i-1) + omegaM*deltaT2[0]) + 2.0L*omegaM/c*2.0L*dLf[i]*beta
              * cosl(omegaM*deltaT2[0]*(long double)(i-1) + omegaM*deltaT2[0]); //uso dLf!!*/
              
//fase approssimata 2 (vedi appunti)
              
phi[i]        =  omega[i]*(2.0L*L0/c)*i + omega[i]*res_t[i] + beta*sinl(omegaM*2.0L*L0/c*i + omegaM*res_t[i]) ;


// tengo ora conto delle variazioni in lunghezza inserendo un nuovo termine di
// variazione di fase

//phi[i]        = phi[i] + (omega[i]/c)*(deltaX2 - deltaX1)*2.0L;

//********** campo incidente************************************************

Einc[i]       = polar (abs(Ainc),phi[i]);

//********** campo interno *************************************************

Eplus[i]      = ta*Einc[i] + ra*rb*Eplus[i-1];

//********** campo riflesso ************************************************

Erifl[i]      = -ra*Einc[i]+rb*ta*Eplus[i-1];

//********** intensità riflessa ********************************************

Irifl[i]      = pow(abs(Erifl[i]),2.0L);

//********** pre-amp fotodiodo *********************************************

cor_foto = bs*pow(1.0L-bs,2.0L)*Irifl[i]; //si tiene conto di R_bs = 0.035

Vhp[i] = hpf(cor_foto,Rhp,Lhp,Vhp[i-1],cor_foto_old, deltaT2[i-1]); //filtro passa alto

cor_foto_old = cor_foto;
//********** mixer del segnale *********************************************

mixed_sign[i] = 0.5L*Vhp[i]*sin( omegaM*deltaT2[0]*i + omegaM*res_t[i] + mix_phase ); //dove 0.5 è l'efficienza del mixer //Vhp[i] o cor_foto

//********** elettronica di amplificazione *********************************

               
//********** blocco A ******************************************************

Vin_A[i]  = mixed_sign[i];
Vout_A[i] = bloccoA( R1_A,C1_A ,Vin_A[i], Vout_A[i-1], deltaT2[i-1]); 

//********** blocco B ******************************************************

Vin_B[i]     =   Vout_A[i]; 
Vout_B[i]    =   amp_inv(R1_B , R2_B, R_B , Rout_B , Cout_B , deltaT2[i-1] , Vin_B[i] , Vout_B[i-1], G);
//Vout_B[i]    =    amp_invID( R1_B,R2_B,Vin_B[i]);


//********** blocco C ******************************************************

Vin_C[i]   =   Vout_B[i]; 
Vout_C[i]  =   integratore1(R1_C,R2_C,R_C,Rout_C,Cout_C,C1_C,deltaT2[i-1],Vin_C[i],Vin_C[i-1],Vc_C[i-1],Vout_C[i-1],G);
Vc_C[i]    =   integratore2(R1_C,R2_C,R_C,Rout_C,Cout_C,C1_C,deltaT2[i-1],Vin_C[i],Vin_C[i-1],Vc_C[i-1],Vout_C[i-1],Vout_C[i],G);
//Vout_C[i]  = integratoreID(R1_C,R2_C,C1_C,deltaT2[i-1],Vin_C[i],Vin_C[i-1],Vout_C[i-1]);

//interruttore esterno per i blocchi di integrazione


if(i>=10000){    // 10000 usato come standard nei test fatti sino ad ora.

//********** blocco D ******************************************************

Vin_D[i]   =   Vout_C[i]; 
Vout_D[i]  =   integratore1(R1_D,R2_D,R_D,Rout_D,Cout_D,C1_D,deltaT2[i-1],Vin_D[i],Vin_D[i-1],Vc_D[i-1],Vout_D[i-1],G);
Vc_D[i]    =   integratore2(R1_D,R2_D,R_D,Rout_D,Cout_D,C1_D,deltaT2[i-1],Vin_D[i],Vin_D[i-1],Vc_D[i-1],Vout_D[i-1],Vout_D[i],G);
//Vout_D[i]  = integratoreID(R1_D,R2_D,C1_D,deltaT2[i-1],Vin_D[i],Vin_D[i-1],Vout_D[i-1]);

//********** blocco E ******************************************************

Vin_E[i]   =   Vout_D[i]; 
Vout_E[i]  =   integratore1(R1_E,R2_E,R_E,Rout_E,Cout_E,C1_E,deltaT2[i-1],Vin_E[i],Vin_E[i-1],Vc_E[i-1],Vout_E[i-1],G);
Vc_E[i]    =   integratore2(R1_E,R2_E,R_E,Rout_E,Cout_E,C1_E,deltaT2[i-1],Vin_E[i],Vin_E[i-1],Vc_E[i-1],Vout_E[i-1],Vout_E[i],G);
//Vout_E[i]  = integratoreID(R1_E,R2_E,C1_E,deltaT2[i-1],Vin_E[i],Vin_E[i-1],Vout_E[i-1]);

//********** blocco F ******************************************************

Vin_F[i]   = Vout_E[i];



} //if interruttore integratori
else{Vin_F[i] = Vout_C[i];}



Vout_F[i]  = bloccoF1(R1_F,R2_F,R3_F,R_F,Rout_F,Cout_F,C1_F,deltaT2[i-1],Vin_F[i],Vin_F[i-1],Vc_F[i-1],Vout_F[i-1],G);
Vc_F[i]    = bloccoF2(R1_F,R2_F,R3_F,R_F,Rout_F,Cout_F,C1_F,deltaT2[i-1],Vin_F[i],Vin_F[i-1],Vc_F[i-1],Vout_F[i-1],Vout_F[i],G);
//Vout_F[i] = bloccoFID(R1_F,R2_F,R3_F,  C1_F,  deltaT2[i-1],  Vin_F[i],  Vin_F[i-1], Vout_F[i-1]);

//********** blocco G ******************************************************

Vin_G[i]  = Vout_F[i];
//Vout_G[i] = amp_invID( R1_G,R2_G,Vin_G[i]);
Vout_G[i] = amp_inv(R1_G , R2_G, R_G , Rout_G , Cout_G , deltaT2[i-1] , Vin_G[i] , Vout_G[i-1], G);

//********** blocco H ******************************************************

Vin_H[i]  = Vout_E[i];
Vout_H[i] = bloccoH(R1_H, C1_H,Vin_H[i],Vout_H[i-1],deltaT2[i-1]);
//Vout_H[i] = (R1_H,C1_H,Vin_H[i],Vout_H[i-1],deltaT2[i-1] ,V_H[i-1],G,Rout_H,Cout_H,R_H);
//V_H[i]    = bloccoH2(R1_H,C1_H,Vin_H[i], Vout_H[i-1],deltaT2[i-1],V_H[i-1],G, Rout_H,Cout_H,R_H,Vout_H[i]);


//********** blocco I ******************************************************

Vin_I[i]  = Vout_H[i];
Vout_I[i] = amp_inv(R1_I , R2_I, R_I , Rout_I , Cout_I , deltaT2[i-1] , Vin_I[i] , Vout_I[i-1], G);


//********** attuatore piezoelettrico **************************************

Vpz[i] = bloccoA( 50.0L,1.0e-9L ,Vout_G[i], Vpz[i-1], deltaT2[i-1]);

//apz(Vpz[i-1],Cpzf,Rpzf,Rpz1,Vout_G[i],deltaT2[i-1]); //5.0e6L è il fattore di conversione V/Hz

//********** error function ************************************************

error_func_fast[i] = Vpz[i]; 

error_func_slow[i] = Vout_I[i]; 

}//********** FINE CICLO FOR ************************************************

//*********** creazione nuova variabile per FFTW3 ***************************

long double * err_fft      =  new long double[Ncamp-500000];

*err_fft  = {};

for(int i = 499999; i < Ncamp-1; i++) {err_fft[i-499999] = Irifl[i];} //qua posso modificare la variabile da analizzare

//*********** FFTW3 *********************************************************

fftwl_complex* out;

out = (fftwl_complex *) fftwl_malloc(sizeof(fftwl_complex) * ((Ncamp-500000)/2 + 1)); //numero campioni sempre pari!!

fftwl_plan p;                                                                         //creo il piano di fftw3

p = fftwl_plan_dft_r2c_1d(Ncamp-500000, err_fft, out, FFTW_ESTIMATE);                 //inizializzo il piano

fftwl_execute(p);                                                                     //calcolo la fft con fftw3

//**************************************************************************


//********** SCRITTURA SU FILE *********************************************

ofstream realEr;
realEr.open("sign.txt",ios_base::out);

if(realEr.is_open())
{
for(int i = 0 ; i < Ncamp-1; i++) 
{
	realEr  << scientific << deltaT2[0]*i + res_t[i] << "  " << Irifl[i] << "  "<< error_func_fast[i] << "  " << Vout_A[i] << "  "<< -1.6e6L/2.0L/PI+0.1L*i <<  "   "<< dLf[i] <<endl;
} 	
} 
realEr.close();

// file per err_fft in cui si saltano i primi 500000 elementi ****************

ofstream errfft;
errfft.open("errfft.txt",ios_base::out);

if(errfft.is_open())
{
for(int i = 499999 ; i < Ncamp-1; i++) 
{
	errfft  << scientific << tempo[i] << "  " << err_fft[i-499999] <<endl;
} 	
} 
errfft.close();

//********** SCRITTURA FFT ****************************************************

ofstream fft;
fft.open  ("fft.txt",ios_base::out);

long double df = 1.0L/tempo[Ncamp-500000];  //intervallino frequenze

if(fft.is_open())
{
for(int i = 0 ; i < Ncamp-500000; i++)      //ho metà Ncamp frequenze lin indip
{ 
	if(i%2==0){fft << df*(i/2) << "   " << out[i/2][0]*out[i/2][0]+
		out[i/2][1]*out[i/2][1] << endl;} 	
}
} 
fft.close();

//********** SCRITTURA SU SCHERMO ******************************************

cout << "Larghezza riga:  " << larghezza_riga      << endl;
cout << "Frequenza FSR :  " << FSR                 << endl;
cout << "Finesse       :  " << finesse             << endl;
cout << "DeltaT2       :  " << deltaT2[1]          << endl;
cout << "tempo         :  " << tempo[Ncamp-2]      << endl;
cout << "df            :  " << 1.0L/tempo[Ncamp-2] << endl;
cout << "f_max         :  " << 1.0L/deltaT2[1]/2.0L<< endl;
cout << "freqM         :  " << freqM               << endl;
cout << "R             :  " << Ra                  << endl;
cout << "lambda0       :  " << c/freq0             << endl;
cout << "omega0        :  " << omega0              << endl;
cout << "omega_finale  :  " << omega[Ncamp-2]      << endl;

//********** LIBERO MEMORIA ************************************************

delete[] Eplus;
delete[] Einc;
delete[] Erifl;
delete[] deltaT2;
delete[] phi;
delete[] Irifl;
delete[] tempo;
delete[] error_func_slow;
delete[] mixed_sign;

return 0;
}
