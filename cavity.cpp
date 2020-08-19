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
	L = abs( M1.GetX() - M2.GetX() );
	//phase and amplitude of all fields are initially set to 0.0
	Eplus.SetA  (0.0);
	Eplus.SetPhi(0.0);
	Erefl.SetA  (0.0);
	Erefl.SetPhi(0.0);
	Einc.SetA   (0.0);
	Einc.SetPhi (0.0);
	FSR = C/(2.0*L);
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
	Erefl = M1.reflect(Einc) + M1.transmit(etemp);

	//update of the time variable
	TIME = TIME + 2.0*L/C;
}


//f1 ed f2 sono le frequenze iniziali e finali della rampa
void cavity::rampa(laser & las)
{
        AssignLaser(las);
        ofstream out;
        out.open("rampa.txt");

	//laser frequency before rampa
	const double freq0 = las.GetFreq();


	//rampa will scan frequency around the nearer resonance frequency
	double f_res;
	//number of free spectral range
	double nfsr = round(freq0/FSR);
	cout << "nfsr = "<< nfsr << endl;
	cout << "FSR = "<< FSR	<< endl;
	f_res = FSR * nfsr;
	cout << "FSR * nsfr = "<< FSR*nfsr	<< endl;

	//freq boundariies of rampa
	double f1,f2;

	f1 = f_res - 1.0e6;
	f2 = f_res + 1.0e6;

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
                for(int i=0; i<1000; i++)
                {
                        GetNewEF(las);
                }
                ef = GetErefl();
                ir = ef.Intensity();
                out <<setprecision(15) <<
			las.GetFreq() << "\t" << ir << endl;
                //cavity reset before new acquisition
                reset();
        }
        out.close();
	//laser frequency is set to the original frequency once again
	las.SetFreq(freq0);
}

