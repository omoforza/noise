#ifndef CAVITY_H
#define CAVITY_H

#include"mirror.h"
#include"electric_field.h"
#include"cavity.h"
#include"laser.h"

class cavity
{
	public:
		//a cavity is defined by two mirrors
		cavity(mirror & m1, mirror & m2)
		{
			M1 = m1;
			M2 = m2;
			Init();
		}
		~cavity() {}

		void GetNewEF(laser &);

		//assign a laser to the cavity
		void AssignLaser(laser &);

		double GetL() {return L;}

		electric_field GetEinc() {return Einc;}
		electric_field GetErefl(){return Erefl;}
		electric_field GetEplus(){return Eplus;}
		double GetTime(){return TIME;}

		//cavity reset function: all fields are destroyed
		void reset() {Init();}

		//rampa is used to obtain the reflected intensity of
                //a cavity as a function of laser frequency
                void rampa(laser &);

	private:
		//distance at equilibrium between laser and first mirror
		//of the cavity
		double D0 = 0.0;
		//class initialization function
		void Init();
		mirror M1;
		mirror M2;
		//cavity length L is defined as the distance between
		//the two mirror M1 and M2
		double L;
		//this field corresponds to the right moving
		// internal field (laser ---->>> cavity)
		electric_field Eplus;
		//this is the field reflected by the cavity
		electric_field Erefl;
		//this is the incident field: just before touching
		//the first mirror
		electric_field Einc;
		
		//temporary electric field for internal use
		electric_field etemp;

		//the cavity is the clock ticking the time of the
		//simulation. The roundtrip of radiation is our variable
		//deltaT
		double TIME = 0.0;

		double FSR;

		const double C = 299792458.0;
};

#endif
