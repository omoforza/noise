#ifndef LASER_H
#define LASER_H

#include"electric_field.h"

class laser
{
	public:
		// the laser is characterized by a frequency [Hz] and a 
		// space coordinate  x [m]
		laser(double lambda = 1064.0e-9, double x = 0.0) :
			LAMBDA(lambda), X(x)
		{
			FREQ = C/lambda;
		}
		~laser() {}
		//this function generates an electric field
		void GenEF(electric_field &);

	private:
		double FREQ;
		const double C = 299792458.0;
		double LAMBDA;
		double X;
}

#endif
