#ifndef MIRROR_H
#define MIRROR_H

#include"electric_field.h"

class mirror
{
	public:
		//r is the amblitude of the coefficient of reflection
		//phi is the phase change due to reflection
		//a is the absorption so that r*r+t*t = 1-a
		//position in m from the laser or the origin
		mirror(double r = 0.5, double phir = 0.0, double at = 0.0,
		double ar = 0.0, double t = 0.5, double phit = 0.0, 
		double x = 0.0):
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
		electric_field reflect (electric_field &);
		electric_field transmit(electric_field &);

		double GetX(){return X;}
		double GetPhir() {return PHIR;}
		void SetPhir(double phi) {PHIR = phi;}

	private:
		double R;
		double PHIR;
		double PHIT;
		double AT;
		double AR;
		double T;
		double X;
};


#endif
