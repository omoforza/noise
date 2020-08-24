#ifndef C_H
#define C_H

class c
{
	public:
		c(double r1 = 4.7e3, double r2 = 4.7e3, double r = 0.5,
		double rout = 4.7e3, double cout = 3.0e-12,
		double c1 = 5.6e-9, double g = 600.0e3):
		R1(r1), R2(r2), R(r), Rout(rout), Cout(cout), C1(c1), G(g)
		{
		V1 = 0.0;
		V1_old = 0.0;
		Vout = 0.0;
		Vout_old = 0.0;
		Vin_old = 0.0;
		}

		double amp(double, double);
	private:
		void step1(double, double);

		double   Rout;
		double      R;
		double   Cout; 
		
		double     R1;
		double     R2;
		double     C1;

		//step1 outputs
		double   V1;
		double   V1_old;

		//step2 outputs and input old
		double   Vout;
		double   Vout_old;
		double   Vin_old;
};

#endif
