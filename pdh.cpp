#include"pdh.h"
#include"electric_field.h"
#include<fstream>
#include<iostream>
#include<iomanip>
#include<fftw3.h>

using std::endl;
using std::cout;
using std::ofstream;
using std::setprecision;

void pdh::ReflIntStatic()
{
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ReflIntS.txt");

        //turn off beta modulation depth        
        long double b = las.GetBeta();
        las.SetBeta(0.0L);

        //laser frequency before rampa
        const long double freq0 = las.GetFreq();

        //rampa will scan frequency around the nearest resonance frequency
        long double f_res = cav.GetFres();

        //freq boundariies of rampa
        long double f1,f2;

	long double FSR = cav.GetFSR();

        f1 = f_res - FSR*0.004L;
        f2 = f_res + FSR*0.004L;

        //number of samples
        int N = 1000;

        //delta frequency
        long double delta;
        delta = (f2 - f1)/(1.0L*N);

        //reflected intensity
        long double ir;
        electric_field ef;

        for(int j=0; j<N; j++)
        {
                las.SetFreq(f1 + delta*j);
                //the cavity charge for 1000 round trip of light
                //before the value of reflected field is stored
                //this number SHOULD be adjusted depending on the
                //reflectivity of mirrors
                for(int i=0; i<7000; i++)
                {
                        cav.GetNewEF(las);
                }
                ef = cav.GetErefl();
                ir = ef.Intensity();
                out <<setprecision(15) <<
                        delta*j-(f2-f1)*0.5L << "\t" << ir << endl;
                //cavity reset before new acquisition
                cav.reset();
		las.reset();
        }
        out.close();
        //laser frequency is set to the original frequency once again
        las.SetFreq(freq0);
        las.SetBeta(b);

	cav.reset();
}

//vel is a velocity in Hz/s
void pdh::ReflIntDynamic(long double vel)
{
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ReflIntD.txt");

        //turn off beta modulation depth        
        long double b = las.GetBeta();
        las.SetBeta(0.0L);

        //laser frequency before the routine was called
        const long double freq0 = las.GetFreq();

        //We will scan frequency around the nearest resonance frequency
        long double f_res = cav.GetFres();

        //freq boundaries
        long double f1,f2;

	long double FSR = cav.GetFSR();

        f1 = f_res - FSR*0.004L;
        f2 = f_res + FSR*0.004L;


        //delta frequency
        long double delta;
	long double dt = cav.GetDT0();

        //number of samples
        int N = int (  round((f2 - f1)/vel/dt)  );
        delta = (f2 - f1)/(1.0L*N);

        //reflected intensity
        long double ir;
        electric_field ef;

	//test
	cout << "Velocità = "<< delta/dt << " Hz/s"<< endl;

        for(int j=0; j<N; j++)
        {
                las.SetFreq(f1 + delta*j);
                cav.GetNewEF(las);
                ef = cav.GetErefl();
                ir = ef.Intensity();
                out << setprecision(15);
	       	out << delta*j-(f2-f1)*0.5L<<"\t";
	        out << ir<< "\t";
	        out << cav.GetErefl() << "\t";
	        out << cav.GetEinc() << "\t";
	        out << cav.GetEplus() << endl;
        }
        out.close();

        //laser frequency is set to the original frequency once again
        las.SetFreq(freq0);
        las.SetBeta(b);

	cav.reset();
	las.reset();
}

void pdh::ChargeCavity(bool in_res)
{
	//if in_res = true the resonance frequency is chosen
	if(in_res){cav.SetResFreq(las);}
	long double b;
	b = las.GetBeta();	
	//the field modulation is turned off
	las.SetBeta(0.0L);
	ofstream out;
	out.open("charge.txt");
	out << setprecision(16);
	electric_field ef;
	for(int i = 0; i < 100000; i++)
	{
		cav.GetNewEF(las);

		out << cav.GetTime()	<< "\t";
		out << cav.GetIrefl()	<< "\t";
	        out << cav.GetErefl()	<< "\t";
	        out << cav.GetEinc()	<< "\t";
	        out << cav.GetEplus()	<< endl;
	}
	out.close();
	cav.reset();
	las.reset();
	las.SetBeta(b);
}

void pdh::ErrorSignal(long double vel)
{
	cav.reset();
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ErrorSignal.txt");
	out<<setprecision(15);

        //this routine will  scan frequency around the nearest
	//resonance frequency
	long double f_res 	= cav.GetFres();
	long double FSR	= cav.GetFSR();	

        //boundaries frequencies
        long double f1,f2;

        f1 = f_res - FSR*0.008L;
        f2 = f_res + FSR*0.008L;

	//to obtain dt I temporarily turn on the laser
	cav.GetNewEF(las);
	long double dt = cav.GetDT();
	//Reset of the cavity. after GetNewEF()
	cav.reset();

	//number of samples
	int N = int ( round( (f2-f1)/vel/dt ) );
        //delta frequency
        long double delta;
        delta = (f2 - f1)/(1.0L*N);

	long double time, intensity, temp;
	bool ind = true;

        for(int j=0; j<N; j++)
        {
                las.SetFreq(f1 + delta*j);
                cav.GetNewEF(las);
                time = cav.GetTime();
                dt = cav.GetDT();
		if(j==1){cout << "Vel Rampa(3.5e8) = "<<delta/dt<<endl;}
                out << delta*j - (f2-f1)*0.5L << "\t";
                intensity = cav.GetIrefl();
                out << intensity << "\t";
		temp = intensity;
                temp = h1.filter(temp,dt);
                temp = 0.5L*temp*sin(las.GetOmegaM()*time + DPhase);
                out << temp << "\t";
                temp = Ampl.ampID(temp, dt, ind, true, out);
		temp = pz.ampID(temp,dt);
                out << AA*temp << endl;

        }
        out.close();
}

void pdh::ErrorStatic()
{
	cav.reset();
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ErrorStatic.txt");
	out<<setprecision(15);

        //this routine will  scan frequency around the nearest
	//resonance frequency
	long double f_res = cav.GetFres();
	long double FSR	= cav.GetFSR();	

        //boundaries frequencies
        long double f1,f2;

        f1 = f_res - FSR*0.008L;
        f2 = f_res + FSR*0.008L;

        //number of samples
        int N = 1000;

        //delta frequency
        long double delta;
        delta = (f2 - f1)/(1.0L*N);
	long double time, dt, intensity, temp;
	bool ind = true;
	bool write = false;

        for(int j=0; j<N; j++)
        {
		write = false;
		cav.reset();
		Ampl.RESET();
		las.reset();
        	cav.AssignLaser(las);
                las.SetFreq(f1 + delta*j);
		for(int k = 0; k<10000; k++){
                cav.GetNewEF(las);
                time = cav.GetTime();
                dt = cav.GetDT();
                intensity = cav.GetIrefl();
		temp = intensity;
                temp = h1.filter(temp,dt);
                temp = 0.5L*temp*sin(las.GetOmegaM()*time + DPhase);
		if(k == 9999){
			write = true;
                	out << delta*j - (f2-f1)*0.5L << "\t";
                	out << intensity << "\t";
                	out << temp << "\t";
		}
                temp = Ampl.ampID(temp, dt, ind, write, out);
		}//end k for
		out << endl;
		Ampl.RESET();

        }//end of j for
        out.close();
	cav.reset();
	las.reset();
}

void pdh::Sim(bool ampStatus)
{
	ofstream out;
	out.open("data.txt");
	out << setprecision(16);

	long double time;
	long double dt;
	long double intensity;
	
	cav.SetResFreq(las);	
	long double res_freq = las.GetFreq();

	long double temp = 0.0L;
	bool ind = false;//turn on or off integration stages in the amp

	ind = true;
	int N = 1000000;
	long double * input = new long double[N];
	//las.ErrSig(2000.0L);
	for(int i=0; i<N; i++)
	{
		if(i==500000) {las.ErrSig(10000.0);}
	        cav.GetNewEF(las);
	        time = cav.GetTime();
	        dt = cav.GetDT();
	        out << time << "\t";
		out << las.GetFreq()-res_freq << "\t";
	        intensity = cav.GetIrefl();
	        out << intensity << "\t";
		input[i] = intensity;
	        temp = h1.filter(intensity,dt);
	        temp = 0.5L*temp*sinl(las.GetOmegaM()*time + DPhase);
	        temp = Ampl.ampID(temp, dt, ind, false, out);
		temp = pz.ampID(temp,dt);
	        temp = temp*AA;
		if(ampStatus) {las.ErrSig(temp);}
	        out << temp << endl;
	}

	out.close();

	fftwl_complex* output;

        output = (fftwl_complex *)fftwl_malloc(sizeof(fftwl_complex)*N/2);

        fftwl_plan plan;

        plan = fftwl_plan_dft_r2c_1d(N,input,output,FFTW_ESTIMATE);

        fftwl_execute(plan);

        ofstream fft;
        out.open("fft.txt");

        for(int i=0; i<N/2; i++){
                out <<1.0L/(N*dt)*i<<"\t" << (output[i][0]*output[i][0] +
                        output[i][1]*output[i][1])<< endl;
        }

	fft.close();
}

void pdh::ErrorEvolution()
{
	cav.reset();
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ErrorEvolution.txt");
	out<<setprecision(15);

        //this routine will  scan frequency around the nearest
	//resonance frequency
	long double f_res = cav.GetFres();
	long double FSR	= cav.GetFSR();	

       
	long double time, dt, intensity, temp;

	cav.reset();
	Ampl.RESET();
	las.reset();
       	cav.AssignLaser(las);

        las.SetFreq(f_res - 100.0L);

	for(int k = 0; k<100000; k++){
              	cav.GetNewEF(las);
      		time = cav.GetTime();
      		dt = cav.GetDT();
              	intensity = cav.GetIrefl();
		temp = intensity;
               	temp = h1.filter(temp,dt);
               	temp = temp*sin(las.GetOmegaM()*time + DPhase);
               	out <<time<<"\t" << intensity << "\t";
               	temp = Ampl.ampID(temp, dt, true, false, out);
		out << temp << "\t";
		temp = pz.ampID(temp,dt);
		out << temp << "\t";
                temp = -1.0L*temp*AA;
		out << temp << endl;
	}//end k for
	Ampl.RESET();
        out.close();
	cav.reset();
	las.reset();
}
