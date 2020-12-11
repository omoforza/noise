#ifndef AMPF_H
#define AMPF_H

class AmpF
{
	public:
		AmpF(
		long double r1 = 4.7e3L,
		long double r2 = 5.6L, 
		long double r3 = 1.0e6L,
		long double r = 0.5L, 
		long double rout = 1000.0L, 
		long double cout = 3.0e-12L, 
		long double c1 = 1.0e-6L, 
		long double g = 600.0e3L
		):

		R1(r1), R2(r2), R3(r3), R(r), Rout(rout), Cout(cout),
		C1(c1), G(g)
		{
			V1 = 0.0;
			V1_old = 0.0;
			Vout = 0.0;
			Vout_old = 0.0;
			Vin_old = 0.0;
		}

		long double amp  (long double, long double);
		long double ampID(long double, long double);

		//RESET function set all parameters to the initial value
                void RESET();

	private:
		long double     R1;
		long double     R2;
		long double     R3;
		long double     C1;
		long double      R;
		long double   Rout;
		long double   Cout;
		long double   G;

		//first step of integration
		void step1(long double, long double);

		//step1 outputs
		long double V1;
		long double V1_old;

		//final step outputs and inputs
		long double Vout;
		long double Vout_old;
		long double Vin_old;
};

#endif
