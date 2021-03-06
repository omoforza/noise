#ifndef PDH_H
#define PDH_H
#include"mirror.h"
#include"cavity.h"
#include"laser.h"
#include"hpf.h"
#include"amplifier.h"
#include"AmpA.h"
#include<math.h>
#include<random>
using namespace std;
class pdh
{
	public:
		pdh	()
		{
		
			cav.AssignLaser(las);

		}
		~pdh	(){}


		long double GetLasFreq(){return las.GetFreq();}

		//APPARATUS TESTING ROUTINES

		//** Reflected intensity of the cavity alone as a function
		//** of frequency. The results are saved in "ReflIntS.txt"
		//** The first column is made up of frequencies, the
		//** second contains intensities.
		//** This routine is called "static" because the intensity
		//** is measured at each frequency after the cavity is 
		//** completely charged. The Dynamic ReflInt() routine
		//** sweeps the frequency at a fixed MHz/s velocity and 
		//** acquires dynamically the reflected intensity
		void ReflIntStatic();
		//** Results are in "ReflIntD.txt"
		//** vel is a velocity in Hz/s  (e.g. 590MHz/s)
		void ReflIntDynamic(long double vel);

		//** Reflected intensity as a function of time. The cavity
		//** is not stabilized during this routine. The only
		//** interaction is between laser and cavity.
		//** This function stores the reflected intensity values 
		//** in: "charge.txt".
		//** If true charge in resonance, if false charge out
		//** of resonance
		void ChargeCavity(bool);

		//** PDH error signal as a function of frequency around
		//** the resonance frequency. The values are all saved
		//** into "ErrorSignal.txt"
		//** This function depends on the sweeping velocity MHz/s
		void ErrorSignal(long double);

		//** PDH error signal STATIC as a function of frequency 
		//** around the resonance frequency. 
		//** The values are all saved into "ErrorStatic.txt"
		void ErrorStatic();

		//** PDH error signal as a function of time fixing the
		//** laser frequency
		void ErrorEvolution();

		//SIMULATION ROUTINES

		//** This routine is the actual simulation, the error 
		//** signal can be fed or not to the laser using a boolean
		//** variable. 
		//** 1. "true" : is fed to the laser
		//** 2. "false": is NOT fed to the laser
		void Sim(bool);

	private:
		//all constant MUST be defined before they are used.
		const long double C = 299792458.0L;
		const long double PI = acos(-1.0L);
		laser las;
		long double R = 0.99L;
		long double R1 = R;
		long double R2 = R;
		mirror m1{sqrt(R1),PI,.0L,.0L,sqrt(1.0L- R1),.0L,.1L};
		mirror m2{sqrt(R2),PI,.0L,.0L,sqrt(1.0L- R2),.0L,0.97L};
		cavity cav{m1,m2};
		hpf h1;
		AmpA pz{1600.0L,1.0e-9L};
		amplifier Ampl{600.0e3L};
		//error signal amplification factor
		const long double AA = -0.8e1L;
		//demodulation phase
		const long double DPhase = PI;

		default_random_engine generator;
		long double STDV = 40.0L;
		long double MEAN = 0.0L;

};
#endif
