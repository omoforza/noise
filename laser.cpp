#include"laser.h"
#include"electric_field.h"
#include<iostream>

using std::cout;
using std::endl;

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
