#include<cmath>
#include<complex>
#include<fstream>

using namespace std;

int main(){

complex<double> F(double);
double Pdc(double , double , double , double);
double PomC(double , double , double , double);
double P2omC(double , double , double , double);
double PomS(double , double , double , double);
double P2omS(double , double , double , double);
double L = 0.87;
double c = 299792458;
double fsr = c/(2.0*L);

double omega = 2.0*acos(-1.0)*1.0/(2.0*(L/c));
double om_mod = 2.0*acos(-1.0)*2.0e6;//717.7e3;//*12.0e6;
double beta = 1.1;
double E0 = 1.0;

ofstream out;
out.open("power.txt");

double freq = 0.0;
double FMAX = 7.0e6;//4.0e6;//50.0e6;
int N = 100000;
double df = 2.0*FMAX/(1.0*N);
for(int i=0; i<N; i++){
omega = 2.0*acos(-1.0)*(df*i - FMAX);

out << -FMAX + df*i 
	     << "\t" << Pdc(beta,omega,om_mod,E0)
	     << "\t" << PomC(beta,omega,om_mod,E0)
	     << "\t" << PomS(beta,omega,om_mod,E0)
	     << "\t" << P2omC(beta,omega,om_mod,E0)
	     << "\t" << P2omS(beta,omega,om_mod,E0)
	     << "\t" << abs(Pdc(beta,omega,om_mod,E0))
	     << "\t" << sqrt(pow(PomC(beta,omega,om_mod,E0),2.0)+ pow(PomS(beta,omega,om_mod,E0),2.0))
	     << "\t" << sqrt(pow(P2omC(beta,omega,om_mod,E0),2.0)+ pow(P2omS(beta,omega,om_mod,E0),2.0))
	     <<endl;
}



}

complex<double> F(double omega){
double r = sqrt(0.99);
complex <double> i(0.0,1.0);
double L = 0.87;
double c = 299792458;
double fsr = c/(2.0*L);

return r*(exp(i*(omega/fsr))-1.0)/(1.0-r*r*exp(i*(omega/fsr)));


}

double Pdc(double beta, double omega, double om_mod, double E0){

	return E0*E0*( pow(abs(F(omega))*cyl_bessel_j(0,beta),2.0)
		     + pow(abs(F(omega+om_mod))*cyl_bessel_j(1,beta),2.0)
		     + pow(abs(F(omega-om_mod))*cyl_bessel_j(1,beta),2.0)
		     ) ;
}

double PomC(double beta, double omega, double om_mod, double E0){
        
        return 2.0*E0*E0*( 
			cyl_bessel_j(0,beta)*cyl_bessel_j(1,beta)
			*real(F(omega)*conj(F(omega-om_mod)) - 
			F(omega+om_mod)*conj(F(omega)) ) 
			+cyl_bessel_j(1,beta)*cyl_bessel_j(2,beta)
			*real(  F(omega-om_mod)*conj(F(omega-2.0*om_mod)) -
                        F(omega+2.0*om_mod)*conj(F(omega+om_mod))   )
			);
}

double PomS(double beta, double omega, double om_mod, double E0){
        
        return 2.0*E0*E0*( 
			cyl_bessel_j(0,beta)*cyl_bessel_j(1,beta)
			*imag(F(omega)*conj(F(omega-om_mod)) - 
			F(omega+om_mod)*conj(F(omega)) )
			+cyl_bessel_j(1,beta)*cyl_bessel_j(2,beta)
                        *imag(  F(omega-om_mod)*conj(F(omega-2.0*om_mod)) -
                        F(omega+2.0*om_mod)*conj(F(omega+om_mod))   )
			);
}

double P2omC(double beta, double omega, double om_mod, double E0){

	return -2.0*E0*E0*pow(cyl_bessel_j(1,beta),2.0)*
		real( F(omega+om_mod)*conj(F(omega-om_mod)) )
		+2.0*E0*E0*cyl_bessel_j(0,beta)*cyl_bessel_j(2,beta)*
		real(F(omega)*conj(F(omega-2.0*om_mod))+conj(F(omega))*
		F(omega+2.0*om_mod))
		;

}

double P2omS(double beta, double omega, double om_mod, double E0){

	return -2.0*E0*E0*pow(cyl_bessel_j(1,beta),2.0)*
		imag( F(omega+om_mod)*conj(F(omega-om_mod)) );
		+2.0*E0*E0*cyl_bessel_j(0,beta)*cyl_bessel_j(2,beta)*
		imag(F(omega)*conj(F(omega-2.0*om_mod))+conj(F(omega))*
		F(omega+2.0*om_mod))
		;

}


