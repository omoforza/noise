#ifndef AMPC_H
#define AMPC_H

class AmpC
{
	public:
		AmpC(
		long double r1 = 4.7e3,
		long double r2 = 4.7e3, 
		long double r = 0.5,
		long double rout = 4.7e3, 
		long double cout = 3.0e-12,
		long double c1 = 5.6e-9, 
		long double g = 600.0e3
		):

		R1(r1), R2(r2), R(r), Rout(rout), Cout(cout), C1(c1), G(g)

		{
		V1 = 0.0;
		V1_old = 0.0;
		Vout = 0.0;
		Vout_old = 0.0;
		Vin_old = 0.0;
		}

		~AmpC(){}
		long double amp  (long double, long double);
		long double ampID(long double, long double);

		//RESET function set all parameters to the initial value
                void RESET();


	private:
		void step1(long double, long double);

		long double	Rout;
		long double	R;
		long double	Cout; 
		long double	G; 
		
		long double	R1;
		long double	R2;
		long double	C1;

		//step1 outputs
		long double	V1;
		long double	V1_old;

		//step2 outputs and input old
		long double	Vout;
		long double	Vout_old;
		long double	Vin_old;
};

#endif
