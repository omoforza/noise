#include"laser.h"
#include"electric_field.h"

void laser::GetField(electric_field & ef, double x, double t)
{
	//phase of the emitted field when it reaches x at time t
	double phi = K*x - OMEGA*(t - x/(2.0*C));
	//intensity of the field
	double In = INTENSITY;
	
	ef.SetA  (In);
	ef.SetPhi(phi);
}
