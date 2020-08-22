#include"a.h"

double a::amp(double Vin, double dt)
{
	double Vout;
	Vout = (V_old + (dt/C1)/R1*Vin)/(1.0L+(dt/C1)/R1);
	return Vout;
}
