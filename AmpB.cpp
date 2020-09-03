#include"AmpB.h"
#include<iostream>

using std::cout;
using std::endl;

double AmpB::amp(double Vin, double dt)
{
	double	Vout;
	double	a = 1.0 + G*R1/(R1+R2) + R/(R1+R2) + R/Rout ;
	double	b = R/(R1+R2) - G*R2/(R1+R2) ;
	double	theta = R*Cout ;

	Vout = (Vout_old + dt/theta*Vin*b)/(1.0 + dt/theta*a);

	Vout_old = Vout;
	
	return Vout;
}



//ideal behavior
double AmpB::ampID(double Vin, double dt)
{
	double Vout;
	Vout = -G*R2/(R1+R2+G*R1)*Vin;
	return Vout;
}
