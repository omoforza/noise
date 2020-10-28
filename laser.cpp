#include"laser.h"
#include"electric_field.h"
#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::endl;
using std::ofstream;

void laser::Init()
{
	FREQ = C/LAMBDA;
	FREQ0 = FREQ;
        OMEGA = 2.0L*PI*FREQ;
        K = 2.0L*PI/LAMBDA;
	N_COUNT = 0;
}

void laser::reset()
{
	SetFreq(FREQ0);
	N_COUNT = 0;
}

electric_field laser::GetField(long double d, long double res_t)
{
	long double phi, In;
	electric_field ef;
	//phase of the emitted field when it reaches x at time t
	phi = K*d - OMEGA*(2.0L*L0/C*N_COUNT) 
		  + OMEGA*res_t
		  + oscillator(res_t);
	//intensity of the field
	In = INTENSITY;
	ef.SetA(In);
	ef.SetPhi(phi);
	N_COUNT++;
	return ef;
}

long double laser::oscillator(long double res_t)
{
long double dphi = beta*sin(omegaM*(2.0L*L0/C*N_COUNT)
		           +omegaM*res_t);
return dphi;
}


void laser::ErrSig(long double err)
{
	SetFreq(FREQ + err);
}



