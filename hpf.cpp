#include"hpf.h"

long double hpf::filter(long double Iin, long double dt)
{
	long double Vout;
	Vout = (V_old + R*(Iin - I_old))/(1.0L + (dt/L)*R ); 
	V_old = Vout;
	I_old = Iin;
	return Vout;
}
