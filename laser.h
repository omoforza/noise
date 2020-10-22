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
			Init();
		}
		~laser() {}


		void SetFreq(double freq)
		{
			LAMBDA = C/freq;
			FREQ = freq;
			OMEGA = 2.0*PI*freq;
        		K = 2.0*PI/LAMBDA;
		}

		void SetBeta(double b){beta = b;}

		double GetIntensity() {return INTENSITY;}
		
		//this function give the electric field in x at time t
		//the field was emitted by the laser at time t - x/c
		//d is the difference in lenght between the laser and the
		//first mirror of the setup from the equilibrium position
		electric_field GetField(double d, long double t);

		double GetX() {return X;}
		double GetBeta() {return beta;}

		double GetFreq(){return FREQ;}

		double GetOmegaM(){return omegaM;}

		//error signal function fed to the laser
		//err signal [Hz]
		void ErrSig(double);

		//reset to initial frequency
		void reset() {SetFreq(FREQ0);}


	private:
		//oscillator is a function of time that modulates the 
		//phase of the emitted field
		double oscillator(double);
		void Init();
		double FREQ;
		//initially defined frequency
		double FREQ0;
		const double PI = acos(-1.0);
		const double C = 299792458.0;
		double LAMBDA;
		double K;
		double OMEGA;
		double X;
		double INTENSITY;
		//phase modulation depth
		double beta		= 0.0;
		const double freqM 	= 0.0;//717.7e3;
		const double omegaM	= 2.0*PI*freqM;
};

#endif
