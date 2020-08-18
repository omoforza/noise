#include"laser.h"
#include"cavity.h"
#include"electric_field.h"
#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::endl;
using std::ofstream;

void laser::Init()
{
	FREQ = C/lambda;
        OMEGA = 2.0*PI*FREQ;
        K = 2.0*PI/LAMBDA;
}

electric_field laser::GetField(double d, double t)
{
	double phi, In;
	electric_field ef;
	//phase of the emitted field when it reaches x at time t
	phi = K*d - OMEGA*(t - d/(2.0*C));
	//intensity of the field
	In = INTENSITY;
	ef.SetA(In);
	ef.SetPhi(phi);

	return ef;
}

//f1 ed f2 sono le frequenze iniziali e finali della rampa
void laser::rampa(cavity cav, double f1, double f2)
{
	cav.AssignLaser(this);
	ofstream out;
	out.open("rampa.txt");

	//number of samples
	int N = 100;

	//delta frequency
	double delta;
	delta = (f2 - f1)/(1.0*N);

	//reflected intensity
	double ir;
	electric_field ef;

	for(int j=0; j<N; j++)
	{
		SetFreq(f1 + delta*j);
		for(int i=0; i<1000; i++)
		{
       			cav.GetNewEF(this);
		}
		ef = cav.GetErefl();
		ir = ef.Intensity();
		out << FREQ << "\t" << ir << endl;
		//cavity reset before new acquisition
		cav.reset();
	}
	out.close();
}
