#include"cavity.h"
#include"electric_field.h"
#include"mirror.h"
#include"laser.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>

using std::cout;
using std::endl;
using std::ofstream;
using std::setprecision;

void cavity::Init()
{
	//the initial distance between the two mirrors is obtained
	L = abs( M1.GetX() - M2.GetX() );

	//phase and amplitude of all fields are initially set to 0.0
	Eplus.SetA  (0.0);
	Eplus.SetPhi(0.0);
	Erefl.SetA  (0.0);
	Erefl.SetPhi(0.0);
	Einc.SetA   (0.0);
	Einc.SetPhi (0.0);

	//the free spectral range frequency
	FSR = C/(2.0*L);
}

void cavity::reset()
{
	TIME	= 0.0;
	DT	= 0.0;

        Eplus.SetA  (0.0);
        Eplus.SetPhi(0.0);
        Erefl.SetA  (0.0);
        Erefl.SetPhi(0.0);
        Einc.SetA   (0.0);
        Einc.SetPhi (0.0);
        etemp.SetA   (0.0);
        etemp.SetPhi (0.0);
}

void cavity::AssignLaser(laser & las)
{
	D0 = M1.GetX() - las.GetX();
}

void cavity::GetNewEF(laser & las)
{
	//The new Einc field is defined on the outer layer of
	//the first mirror
	Einc = las.GetField((M1.GetX()-las.GetX()) - D0, TIME);

	//eplus
	etemp = M2.reflect(Eplus);
	Eplus = M1.transmit(Einc) + M1.reflect(etemp);

	//Using Einc it is possible to define Erefl using the
	//properties of the mirror
	Erefl = M1.ex_reflect(Einc) + M1.transmit(etemp);

	//update of the time variable
	TIME = TIME + 2.0*L/C;
	DT = 2.0*L/C;
}


void cavity::rampa(laser & las)
{
        AssignLaser(las);

	//output file to store data
        ofstream out;
        out.open("ReflInt.txt");

	//turn off beta modulation depth	
	double b = las.GetBeta();
	las.SetBeta(0.0);

	//laser frequency before rampa
	const double freq0 = las.GetFreq();

	//rampa will scan frequency around the nearer resonance frequency
	double f_res;
	//number of time the free spectral range frequency fit into
	//the laser frequency
	double nfsr = round(freq0/FSR);
	//we fix the nearest resonce to laser frequency
	f_res = FSR * nfsr;

	//freq boundariies of rampa
	double f1,f2;

	f1 = f_res - FSR*0.05;
	f2 = f_res + FSR*0.05;

        //number of samples
        int N = 5000;

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
                for(int i=0; i<1000; i++)
                {
                        GetNewEF(las);
                }
                ef = GetErefl();
                ir = ef.Intensity();
                out <<setprecision(18) <<
			delta*j-(f2-f1)*0.5 << "\t" << ir << endl;
                //cavity reset before new acquisition
                reset();
        }
        out.close();
	//laser frequency is set to the original frequency once again
	las.SetFreq(freq0);
	las.SetBeta(b);
}


void cavity::SetResFreq(laser & las)
{
	AssignLaser(las);
	double fres = round(las.GetFreq() / FSR)*FSR;
	las.SetFreq(fres);	
}

