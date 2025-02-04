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
}

void laser::reset()
{
	SetFreq(FREQ0);
	T_OLD = 0.0L;
	PHI_OM_OLD=0.0L;
}

electric_field laser::GetField(long double d, long double t)
{
	long double phi, In;
	electric_field ef;
	long double dt = t - T_OLD;
	//phase of the emitted field when it reaches x at time t
	phi = K*d - PHI_OM_OLD - OMEGA*(dt - d/(2.0L*C)) 
		+ oscillator(t - d/(2.0L*C));
	//intensity of the field
	In = INTENSITY;
	ef.SetA(In);
	ef.SetPhi(phi);
	T_OLD = t;
	PHI_OM_OLD = fmod(PHI_OM_OLD,2.0L*acosl(-1.0L)) 
		+ OMEGA*(dt - d/(2.0L*C)) - K*d;
	return ef;
}

long double laser::oscillator(long double t)
{
long double dphi = beta*sin(omegaM*t);
return dphi;
}


void laser::ErrSig(long double err)
{
	SetFreq(FREQ + err);
}



