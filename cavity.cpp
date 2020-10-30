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
	Eplus.SetA  (0.0L);
	Eplus.SetPhi(0.0L);
	Erefl.SetA  (0.0L);
	Erefl.SetPhi(0.0L);
	Einc.SetA   (0.0L);
	Einc.SetPhi (0.0L);

	//the free spectral range frequency
	FSR	= C/(2.0L*L);
	DT0	= 2.0L*L/C;
}

void cavity::reset()
{
	TIME	= 0.0L;
	DT	= 0.0L;
	RES_T	= 0.0L;

	N_COUNT	= 1;

        Eplus.SetA  (0.0L);
        Eplus.SetPhi(0.0L);
        Erefl.SetA  (0.0L);
        Erefl.SetPhi(0.0L);
        Einc.SetA   (0.0L);
        Einc.SetPhi (0.0L);
        etemp.SetA   (0.0L);
        etemp.SetPhi (0.0L);
}

void cavity::AssignLaser(laser & las)
{
	D0	= M1.GetX() - las.GetX();
	//FRES	= round(las.GetFreq() / FSR)*FSR;
	FRES	= FSR;
}

void cavity::GetNewEF(laser & las)
{
	DT	= 2.0L*L/C;
	RES_T	= RES_T + (DT - DT0); 
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
	TIME = DT0*(long double)N_COUNT + RES_T;
	N_COUNT++;
}


void cavity::rampa(laser & las)
{
        AssignLaser(las);

	//output file to store data
        ofstream out;
        out.open("ReflInt.txt");

	//turn off beta modulation depth	
	long double b = las.GetBeta();
	las.SetBeta(0.0L);

	//laser frequency before rampa
	const long double freq0 = las.GetFreq();

	//rampa will scan frequency around the nearest resonance frequency
	long double f_res = GetFres();

	//freq boundariies of rampa
	long double f1,f2;

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
                        GetNewEF(las);
                }
                ef = GetErefl();
                ir = ef.Intensity();
                out <<setprecision(15) <<
			delta*j-(f2-f1)*0.5L << "\t" << ir << endl;
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
	las.SetFreq(FRES);	
}

