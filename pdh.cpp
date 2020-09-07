#include"pdh.h"
#include"electric_field.h"
#include<fstream>
#include<iomanip>

using std::endl;
using std::ofstream;
using std::setprecision;

void pdh::ReflInt()
{
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ReflInt.txt");

        //turn off beta modulation depth        
        double b = las.GetBeta();
        las.SetBeta(0.0);

        //laser frequency before rampa
        const double freq0 = las.GetFreq();

        //rampa will scan frequency around the nearest resonance frequency
        double f_res = cav.GetFres();

        //freq boundariies of rampa
        double f1,f2;

	double FSR = cav.GetFSR();

        f1 = f_res - FSR*0.004;
        f2 = f_res + FSR*0.004;

        //number of samples
        int N = 1000;

        //delta frequency
        double delta;
        delta = (f2 - f1)/(1.0*N);

        //reflected intensity
        double ir;
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
                        delta*j-(f2-f1)*0.5 << "\t" << ir << endl;
                //cavity reset before new acquisition
                cav.reset();
        }
        out.close();
        //laser frequency is set to the original frequency once again
        las.SetFreq(freq0);
        las.SetBeta(b);

	cav.reset();
}

void pdh::ChargeCavity(bool ind)
{
	if(ind){cav.SetResFreq(las);}
	double b;
	b = las.GetBeta();	
	las.SetBeta(0.0);
	ofstream out;
	out.open("charge.txt");
	out << setprecision(16);
	electric_field ef;
	for(int i = 0; i < 10000; i++)
	{
		cav.GetNewEF(las);
		out << cav.GetTime() << "\t" << cav.GetIrefl() << endl;
	}
	out.close();
	cav.reset();
	las.SetBeta(b);
}

void pdh::ErrorSignal()
{
	cav.reset();
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ErrorSignal.txt");
	out<<setprecision(15);

        //this routine will  scan frequency around the nearest
	//resonance frequency
	double f_res 	= cav.GetFres();
	double FSR	= cav.GetFSR();	

        //boundaries frequencies
        double f1,f2;

        f1 = f_res - FSR*0.004;
        f2 = f_res + FSR*0.004;

        //number of samples
        int N = 1000000;

        //delta frequency
        double delta;
        delta = (f2 - f1)/(1.0*N);
	double time, dt, intensity, temp;
	bool ind = true;

        for(int j=0; j<N; j++)
        {
                las.SetFreq(f1 + delta*j);
                cav.GetNewEF(las);
                time = cav.GetTime();
                dt = cav.GetDT();
                out << delta*j - (f2-f1)*0.5 << "\t";
                intensity = cav.GetIrefl();
                out << intensity << "\t";
                temp = h1.filter(intensity,dt);
                temp = temp*sin(las.GetOmegaM()*time + DPhase);
                out << temp << "\t";
                temp = Ampl.ampID(temp, dt, ind);
		temp = pz.ampID(temp,dt);
                temp = temp*AA;
                out << temp << endl;

        }
        out.close();
}

void pdh::Sim(bool ampStatus)
{
	ofstream out;
	out.open("data.txt");
	out << setprecision(16);

	double time;
	double dt;
	double intensity;
	
	cav.SetResFreq(las);	

	double temp = 0.0;
	bool ind = false;//turn on or off integration stages in the amp
	for(int i=0; i<10000; i++)
	{
	        cav.GetNewEF(las);
	        time = cav.GetTime();
	        dt = cav.GetDT();
	        out << time << "\t";
	        intensity = cav.GetIrefl();
	        out << intensity << "\t";
	        temp = h1.filter(intensity,dt);
	        temp = temp*sin(las.GetOmegaM()*time + DPhase);
	        temp = Ampl.ampID(temp, dt, ind);
		temp = pz.ampID(temp,dt);
	        temp = temp*AA;
		if(ampStatus) {las.ErrSig(temp);}
	        out << temp << endl;
	}
	out.close();
}
