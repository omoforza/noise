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

	private:
		//all constant MUST be defined before they are used.
		const double C = 299792458.0;
		const double PI = acos(-1.0);
		laser las;
		mirror m1{0.99,PI,0.0,0.0,sqrt(1.0-0.99*0.99),0.0,0.1};
		mirror m2{0.99,PI,0.0,0.0,sqrt(1.0-0.99*0.99),0.0,1.1};
		cavity cav{m1,m2};
		hpf h1;
		AmpA pz{50.0,1.0e-9};
		amplifier Ampl{600.0e3};

};
#endif