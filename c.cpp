#include"c.h"

void c::step1(double Vin, double dt)
{

double A     = (-1.0-R/Rout)/R/Cout ;
double B     = (-G-R/R1)/R/Cout ;
double theta = 1.0/R1/Cout;

V1 = (V1_old*(1.0L-(1.0L+R2/R1)/dt/B-1.0L/C1/R1/B)
+Vin*(-theta/B*(1.0L+R2/R1)-R2/R1-dt/C1/R1-theta/B*dt/C1/R1)
-Vout_old*(1.0L+R2/R1)
+Vin_old*(R2/R1))
/
(1.0L-(1.0L+R2/R1)*(1.0L-dt*A)/dt/B-(1.0L-dt*A)/B/C1/R1);
}

double c::amp(double Vin, double dt)
{
	//run step1 before this function
	step1(Vin, dt);

	double A     = (-1.0L-R/Rout)/R/Cout ;
	double B     = (-G-R/R1)/R/Cout ;
	double theta = 1.0L/R1/Cout;


	Vout = V1*(1.0-dt*A)/dt/B-V1_old/dt/B-theta/B*Vin;
	//update of the old variables before return
	V1_old = V1;
	Vout_old = Vout;
	return Vout;
}
