#ifndef PDH_H
#define PDH_H
#include"mirror.h"
#include"cavity.h"
#include"laser.h"
#include"hpf.h"
#include"amplifier.h"
#include"AmpA.h"
#include<math.h>
class pdh
{
	public:
		pdh	()
		{
		
			cav.AssignLaser(las);

		}
		~pdh	(){}


		double GetLasFreq(){return las.GetFreq();}

		//APPARATUS TESTING ROUTINES

		//** Reflected intensity of the cavity alone as a function
		//** of frequency. The results are saved in "ReflInt.txt"
		//** The first column is made up of frequencies, the
		//** second contains intensities.
		void ReflInt();

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
		void ErrorSignal();

		//SIMULATION ROUTINES

		//** This routine is the actual simulation, the error 
		//** signal can be fed or not to the laser using a boolean
		//** variable. 
		//** 1. "true" : is fed to the laser
		//** 2. "false": is NOT fed to the laser
		void Sim(bool);

	private:
		//all constant MUST be defined before they are used.
		const double C = 299792458.0;
		const double PI = acos(-1.0);
		laser las;
		double R = 0.99826;
		mirror m1{sqrt(R),PI,.0,.0,sqrt(1.- R),.0,.1};
		mirror m2{sqrt(R),PI,.0,.0,sqrt(1.- R),.0,.985};
		cavity cav{m1,m2};
		hpf h1;
		AmpA pz{50.0,1.0e-9};
		amplifier Ampl{600.0e3};
		//error signal amplification factor
		const double AA = 1.0e10;

		const double DPhase = PI*0.5;

};
#endif
