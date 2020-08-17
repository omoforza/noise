#ifndef LASER_H
#define LASER_H

#include"electric_field.h"
#include<cmath>

class laser
{
	public:
		// the laser is characterized by a frequency [Hz] and a 
		// space coordinate  x [m]
		laser(double lambda = 1064.0e-9, double x = 0.0,
		      double intensity = 1.0) :
			LAMBDA(lambda), X(x), INTENSITY(intensity)
		{
			FREQ = C/lambda;
			OMEGA = 2.0*PI*FREQ;
			K = 2.0*PI/LAMBDA;

		}
		~laser() {}

		double GetIntensity() {return INTENSITY;}
		
		//this function give the electric field in x at time t
		//the field was emitted by the laser at time t - x/c
		//d is the difference in lenght between the laser and the
		//first mirror of the setup from the equilibrium position
		void GetField(electric_field &, double d, double t);

		double GetX() {return X;}

	private:
		double FREQ;
		const double PI = acos(-1.0);
		const double C = 299792458.0;
		double LAMBDA;
		double K;
		double OMEGA;
		double X;
		double INTENSITY;
};

#endif
