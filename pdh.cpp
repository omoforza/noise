#include"pdh.h"
#include"electric_field.h"
#include<fstream>
#include<iomanip>

using std::endl;
using std::ofstream;
using std::setprecision;

void pdh::ReflInt()
{
	cav.rampa(las);
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
/*
void pdh::ErrorSignal()
{
	cav.reset();
        cav.AssignLaser(las);

        //output file to store data
        ofstream out;
        out.open("ErrorSignal.txt");

        //this routine will  scan frequency around the nearest
	//resonance frequency
        double f_res;
        //number of time the free spectral range frequency fit into
        //the laser frequency
        double nfsr = round(freq0/FSR);
        //we fix the nearest resonce to laser frequency
        f_res = FSR * nfsr;

        //boundaries frequencies
        double f1,f2;

        f1 = f_res - FSR*0.1;
        f2 = f_res + FSR*0.1;

        //number of samples
        int N = 1000;

        //delta frequency
        double delta;
        delta = (f2 - f1)/(1.0*N);

        for(int j=0; j<N; j++)
        {
                las.SetFreq(f1 + delta*j);
                //the cavity charge for 1000 round trip of light
                for(int i=0; i<1000; i++)
                {
//                        GetNewEF(las);
                }
                //out <<setprecision(18) <<
                //cavity reset before new acquisition
                cav.reset();
        }
        out.close();
}
*/
void pdh::Sim(bool ampStatus, double freq)
{
	ofstream out;
	out.open("data.txt");
	out << setprecision(16);

	double time;
	double dt;
	double intensity;
	electric_field ef;
	
	cav.SetResFreq(las);	

	double temp = 0.0;
	for(int i=0; i<100000; i++)
	{
	        cav.GetNewEF(las);
	        ef = cav.GetErefl();
	        time = cav.GetTime();
	        dt = cav.GetDT();
	        out << time << "\t";
	        intensity = ef.Intensity();
	        out << intensity << "\t";
	        temp = h1.filter(intensity,dt);
	        temp = temp*sin(las.GetOmegaM()*time - PI*0.5);
	        temp = Ampl.ampID(temp, dt);
	        temp = temp*10.0e7;
		if(ampStatus) {las.ErrSig(temp);}
	        out << temp << endl;
	}
	out.close();
}
