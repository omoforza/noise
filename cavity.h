#ifndef CAVITY_H
#define CAVITY_H

#include"mirror.h"
#include"electric_field.h"
#include"cavity.h"
#include"laser.h"

class cavity
{
	public:
		//a cavity is defined by two mirrors parallels to 
		//each other
		cavity(mirror & m1, mirror & m2)
		{
			M1 = m1;
			M2 = m2;
			Init();
		}
		~cavity() {}

		//this function enablle the interaction between a laser
		//and the cavity. It updates the internal and reflected
		//electric fields starting from the inciddent field from
		//the laser
		void GetNewEF(laser &);

		//assign a laser to the cavity
		//This function assign a particular laser to the cavity
		//It defines the initial distance between them.
		//This distance is then used as the equilibrium
		//distance during vibrations
		//SHOULD BE CALLED BEFORE GetNewEf()
		void AssignLaser(laser &);

		//Getters
		long double		GetDT()	   {return DT;}
		long double		GetL()	   {return L;}
		long double		GetTime()  {return TIME;}
		electric_field	GetEinc()  {return Einc;}
		electric_field 	GetErefl() {return Erefl;}
		electric_field 	GetEplus() {return Eplus;}
		long double		GetIrefl() {return Erefl.Intensity();}
		long double		GetFres()  {return FRES;}
		long double		GetFSR()  {return FSR;}

		//cavity reset function: all fields are set to zero
		void reset();

		//rampa is used to obtain the reflected intensity of
                //a cavity as a function of laser frequency
		//it scans the frequency around the nearer resonance to
		//actual laser frequency
                void rampa(laser &);

		//set resonance frequency in the coupled laser
		void SetResFreq(laser & las);

	private:
		//distance at equilibrium between laser and first mirror
		//of the cavity
		long double D0 = 0.0L;

		//class initialization function
		void Init();

		//The two cavity mirrors
		//The spatial order is from left to right:
		//		(LASER) --> (M1)-----(M2)
		mirror M1;
		mirror M2;

		//cavity length L is defined as the distance between
		//the two mirror M1 and M2
		long double L;

		//this field corresponds to the right moving
		// internal field (laser ---->>> cavity)
		electric_field Eplus;

		//this is the field reflected by the cavity
		electric_field Erefl;

		//this is the incident field: just before touching
		//the first mirror (M1)
		electric_field Einc;
		
		//temporary electric field for internal use
		electric_field etemp;

		//the cavity is the clock ticking the time of the
		//simulation. The roundtrip of radiation is our variable
		//deltaT
		long double TIME	= 0.0L;
		long double DT		= 0.0L;
		long double DT0		= 0.0L;
		long double RES_T	= 0.0L;

		int N_COUNT = 1;

		//Theoretical free spectral range of the laser-cavity set
		long double FSR;

		//speed of light in m/s
		const long double C = 299792458.0L;

		//resonance frequency associated to the associated laser
		long double FRES;
};

#endif
