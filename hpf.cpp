#include"hpf.h"

double hpf::filter(double Iin, double dt)
{
	double Vout;
	Vout = (Vold + R*(Iin - Iold))/(1.0L + dt*R/L )/R; 
	V_old = Vout;
	I_old = Iin;
}
