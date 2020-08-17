#include"laser.h"
#include"electric_field.h"
#include<iostream>

using std::cout;
using std::endl;

void laser::GetField(electric_field & ef, double d, double t)
{
	//phase of the emitted field when it reaches x at time t
	double phi = K*d - OMEGA*(t - d/(2.0*C));
	//intensity of the field
	double In = INTENSITY;
	ef.SetA  (In);
	ef.SetPhi(phi);
}
