#include"AmpB.h"
#include<iostream>

using std::cout;
using std::endl;

long double AmpB::amp(long double Vin, long double dt)
{
	long double	Vout;
	long double	a = 1.0 + G*R1/(R1+R2) + R/(R1+R2) + R/Rout ;
	long double	b = R/(R1+R2) - G*R2/(R1+R2) ;
	long double	theta = R*Cout ;

	Vout = (Vout_old + dt/theta*Vin*b)/(1.0 + dt/theta*a);

	Vout_old = Vout;
	
	return Vout;
}



//ideal behavior
long double AmpB::ampID(long double Vin, long double dt)
{
	long double Vout;
	Vout = -G*R2/(R1+R2+G*R1)*Vin;
	return Vout;
}

void AmpB::RESET(){
Vout_old = 0.0;
}
