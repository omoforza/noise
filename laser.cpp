#include"laser.h"
#include"electric_field.h"
#include<iostream>

using std::cout;
using std::endl;

void laser::GetField(electric_field & ef, double dist, double t)
{
	//phase of the emitted field when it reaches x at time t
	double phi = K*dist - OMEGA*(t - dist/(2.0*C));
	//intensity of the field
	double In = INTENSITY;

	cout << "K = " << K << endl;
	cout << "OMEGA = " << OMEGA << endl;
	cout << "dist = " << dist << endl;
	
	ef.SetA  (In);
	ef.SetPhi(phi);
}
