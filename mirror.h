#ifndef MIRROR_H
#define MIRROR_H

#include<electric_field.h>

class mirror
{
	public:
		//r is the amblitude of the coefficient of reflection
		//phi is the phase change due to reflection
		//a is the absorption so that r*r+t*t = 1-a
		//position in m from the laser or the origin
		mirror(double r = 0.5, double phir = 0.0, double a = 0.0,
		double t = 0.5, double phit = 0.0, double x = 0.0):
			R(r), PHIR(phi), A(a), PHIT (phit), T(t), X(x)
		{
			
		}
		void reflect (electric field &);
		void transmit(electric field &);
	private:
		double R;
		double PHIR;
		double PHIT;
		double A;
		double T;
		double X;
}


#endif
