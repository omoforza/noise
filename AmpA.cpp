#include"AmpA.h"

long double AmpA::ampID(long double Vin, long double dt)
{
	long double Vout;
	Vout = (V_old + (dt/C1)/R1*Vin)/(1.0L+(dt/C1)/R1);
	//store the new V_old value
	V_old = Vout;
	return Vout;
}

long double AmpA::amp(long double Vin, long double dt)
{
	long double Vout;
	Vout = (V_old + dt/C1/R1*Vin)/(1.0+(dt/C1)/R1);
	//store the new V_old value
	V_old = Vout;
	return Vout;
}

void AmpA::RESET(){
V_old = 0.0;
}
