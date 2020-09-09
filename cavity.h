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
		double		GetDT()	   {return DT;}
		double		GetL()	   {return L;}
		double		GetTime()  {return TIME;}
		electric_field	GetEinc()  {return Einc;}
		electric_field 	GetErefl() {return Erefl;}
		electric_field 	GetEplus() {return Eplus;}
		double		GetIrefl() {return Erefl.Intensity();}
		double		GetFres()  {return FRES;}
		double		GetFSR()  {return FSR;}

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
		double D0 = 0.0;

		//class initialization function
		void Init();

		//The two cavity mirrors
		//The spatial order is from left to right:
		//		(LASER) --> (M1)-----(M2)
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
		//the first mirror (M1)
		electric_field Einc;
		
		//temporary electric field for internal use
		electric_field etemp;

		//the cavity is the clock ticking the time of the
		//simulation. The roundtrip of radiation is our variable
		//deltaT
		double TIME = 0.0;
		double DT = 0.0;

		//Theoretical free spectral range of the laser-cavity set
		double FSR;

		//speed of light in m/s
		const double C = 299792458.0;

		//resonance frequency associated to the associated laser
		double FRES;
};

#endif
