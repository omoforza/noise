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
				intensity= 1.0) :
			LAMBDA(lambda), X(x), INTENSITY(intensity)
		{
			FREQ = C/lambda;
			PI = acos(-1.0);
			OMEGA = 2.0*PI*FREQ;

		}
		~laser() {}

		double GetIntensity() {return INTENSITY;}
		double Get

	private:
		double FREQ;
		const double PI;
		const double C = 299792458.0;
		double LAMBDA;
		double OMEGA;
		double X;
		double INTENSITY;
};

#endif
