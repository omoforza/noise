#include"b.h"

double b::amp(double Vin, double dt)
{
	double	Vout;
	double	a = -1.0 -G*R1/(R1+R2)-R/R2+R/R2*R1/(R1+R2)-R/Rout ;
	double	b = -G*R2/(R1+R2)+R/(R1+R2) ;
	double	theta = R*Cout ;

	Vout = (Vout_old + dt*b/theta*Vin)/(1.0L-dt*a/theta)

	Vout_old = Vout;
	
	return Vout;
}
