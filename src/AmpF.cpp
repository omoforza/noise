#include"AmpF.h"

void AmpF::step1(long double Vin, long double dt)
{
long double        a = (1.0/R+1.0/Rout)/Cout;
long double        S = -1.0/Cout*(1.0/R1+G/R);
long double    theta = 1.0/(R1*Cout);
long double    alpha = 1.0/R1+R2/R1/R3;
long double    gamma = C1*(R2/R1);
long double    beta1 = 1.0/R1+(R1+R2)/R1/R3;
long double    delta = C1/R1*(R1+R2);

V1 = (V1_old*(1.0-beta1/(C1*S)-delta/(C1*dt*S))
-Vin*(delta*theta/(C1*S)+dt*beta1*theta/(C1*S)+gamma/C1+dt*(alpha/C1))
-delta/C1*Vout_old
+gamma/C1*Vin_old
)/(1.0-delta/(C1*dt*S)*(1.0+dt*a)
+dt/(R3*C1)
-beta1/(C1*S)*(1.0+dt*a)
);

}


long double AmpF::amp(long double Vin, long double dt)
{
//step1 is called first to update V1 value
step1(Vin,dt);

long double        a = (1.0/R+1.0/Rout)/Cout;
long double        S = -1.0/Cout*(1.0/R1+G/R);
long double    theta = 1.0/(R1*Cout);

Vout = V1*(1.0L+dt*a)/(dt*S)-V1_old/(dt*S)-(theta/S)*Vin;

V1_old = V1;
Vout_old = Vout;
Vin_old = Vin;

return Vout;
}


long double AmpF::ampID(long double Vin, long double dt)
{
	Vout = (Vout_old - (R2+R3)/R1/R3*dt*Vin - R2/R1*(Vin-Vin_old))
		/(1.0+dt/C1/R3);
	Vout_old = Vout;
	Vin_old = Vin;
	return Vout;
}

void AmpF::RESET(){
                V1 = 0.0;
                V1_old = 0.0;
                Vout = 0.0;
                Vout_old = 0.0;
                Vin_old = 0.0;
}


