#ifndef LASER_H
#define LASER_H

#include"electric_field.h"
#include<math.h>

class laser
{
	public:
		// the laser is characterized by a frequency [Hz] and a 
		// space coordinate  x [m]
		laser(long double lambda=1064.0e-9L, long double x=0.0L,
		      long double intensity = sqrt(40.0e-3L)) :
			LAMBDA(lambda), X(x), INTENSITY(intensity)
		{
			Init();
		}
		~laser() {}


		void SetFreq(long double freq)
		{
			LAMBDA = C/freq;
			FREQ = freq;
			OMEGA = 2.0L*PI*freq;
        		K = 2.0L*PI/LAMBDA;
		}

		void SetBeta(long double b){beta = b;}
		void SetInt(long double intensity){INTENSITY = intensity;}

		long double GetIntensity() {return INTENSITY;}
		
		//this function give the electric field in x at time t
		//the field was emitted by the laser at time t - x/c
		//d is the difference in lenght between the laser and the
		//first mirror of the setup from the equilibrium position
		electric_field GetField(long double d, long double t);

		long double GetX() {return X;}
		long double GetBeta() {return beta;}

		long double GetFreq(){return FREQ;}

		long double GetOmegaM(){return omegaM;}

		//error signal function fed to the laser
		//err signal [Hz]
		void ErrSig(long double);

		//reset to initial frequency
		void reset();


	private:
		//oscillator is a function of time that modulates the 
		//phase of the emitted field
		long double oscillator(long double);
		void Init();
		long double FREQ;
		//initially defined frequency
		long double FREQ0;
		const long double PI = acos(-1.0L);
		const long double C = 299792458.0L;
		long double LAMBDA;
		long double K;
		long double OMEGA;
		long double X;
		long double T_OLD=0.0L;
		long double PHI_OM_OLD=0.0L;
		long double INTENSITY;
		//phase modulation depth
		long double beta		= 1.1L;
		const long double freqM 	= 717.7e3L;
		const long double omegaM	= 2.0L*PI*freqM;
};

#endif
