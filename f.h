#ifndef F_H
#define F_H

class f
{
	public:
		f(double r1 = 4.7e3, double r2 = 5.6, double r3 = 1.0e6,
		double r = 0.5, double rout = 1000.0, 
		double cout = 3.0e-12, double c1 = 1.0e-6, 
		double g = 600.0e3):
		R1(r1), R2(r2), R3(r3), R(r), Rout(rout), Cout(cout),
		C1(c1), G(g)
		{
			V1 = 0.0;
			V1_old = 0.0;
			Vout = 0.0;
			Vout_old = 0.0;
			Vin_old = 0.0;
		}

		double amp(double, double);
	private:
		double     R1;
		double     R2;
		double     R3;
		double     C1;
		double      R;
		double   Rout;
		double   Cout;

		//first step of integration
		void step1(double, double);

		//step1 outputs
		double V1;
		double V1_old;

		//final step outputs and inputs
		double Vout;
		double Vout_old;
		double Vin_old;
};

#endif
