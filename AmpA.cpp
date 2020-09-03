#include"AmpA.h"

double AmpA::ampID(double Vin, double dt)
{
	double Vout;
	Vout = (V_old + (dt/C1)/R1*Vin)/(1.0+(dt/C1)/R1);
	//store the new V_old value
	V_old = Vout;
	return Vout;
}

double AmpA::amp(double Vin, double dt)
{
	double Vout;
	Vout = (V_old + dt/C1/R1*Vin)/(1.0+(dt/C1)/R1);
	//store the new V_old value
	V_old = Vout;
	return Vout;
}
