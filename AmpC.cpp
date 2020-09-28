#include"AmpC.h"

void AmpC::step1(double Vin, double dt)
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

double AmpC::amp(double Vin, double dt)
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


double AmpC::ampID(double Vin, double dt)
{
	double Vout;
	Vout = Vout_old - R2/R1*(Vin - Vin_old) - dt/(R1*C1)*Vin;
	Vout_old = Vout;
	Vin_old = Vin;
	return Vout;
}

void AmpC::RESET(){
		V1 = 0.0;
                V1_old = 0.0;
                Vout = 0.0;
                Vout_old = 0.0;
                Vin_old = 0.0;
}
