#ifndef MIRROR_H
#define MIRROR_H

#include"electric_field.h"
#include<math.h>

class mirror
{
	public:
		//r is the amblitude of the coefficient of reflection
		//phi is the phase change due to reflection
		//a is the absorption so that r*r+t*t = 1-a
		//position in m from the laser or the origin
		mirror(
		long double r = 0.5L, 
		long double phir = 0.0L, 
		long double at = 0.0L,
		long double ar = 0.0L, 
		long double t = 0.5L, 
		long double phit = 0.0L, 
		long double x = 0.0L
		):
			R(r), PHIR(phir), AT(at), AR(ar), PHIT (phit),
		       	T(t), X(x)
		{
			
		}
		~mirror() {}
		mirror (const mirror & m)
		{
			R 	= m.R;
			PHIR 	= m.PHIR;
			PHIT 	= m.PHIT;
			AT 	= m.AT;
			AR 	= m.AR;
			T 	= m.T;
			X 	= m.X;
			
		}
		//every mirror can interact with an electrifield.
		//In particular it can reflect, externally reflect and 
		//transmit light. external reflection (interface from 
		//higher n to lower. e.g. glass ---> air)
		electric_field reflect (electric_field);
		electric_field ex_reflect (electric_field);
		electric_field transmit(electric_field);

		//Getters
		long double GetX(){return X;}
		long double GetPhir() {return PHIR;}

		//Setters
		void SetPhir(long double phi) {PHIR = phi;}

	private:
		long double R;
		long double PHIR;
		long double PHIT;
		long double AT;
		long double AR;
		long double T;
		long double X;
};


#endif
