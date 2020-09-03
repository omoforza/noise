#include"hpf.h"

double hpf::filter(double Iin, double dt)
{
	double Vout;
	Vout = (V_old + R*(Iin - I_old))/(1.0L + dt*R/L )/R; 
	V_old = Vout;
	I_old = Iin;
	return Vout;
}
