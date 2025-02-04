#ifndef AMPB_H
#define AMPB_H

class AmpB
{
	public:
		AmpB(
		long double r1 = 333.0,
		long double r2 = 6.7e3,
		long double r = 0.01,
		long double rout = 4.3e8,
		long double cout = 3.0e-15,
		long double g = 600.0e3
		):
		R1(r1), R2(r2), R(r), Rout(rout), Cout(cout), G(g)
		{
			Vout_old = 0.0;
		}

		//amplifier stage and IDeal implifier stage
		long double amp (long double, long double);
		//ideal
		long double ampID(long double, long double);

		//RESET function set all parameters to the initial value
                void RESET();


	private:
		long double	R1;
		long double	R2;
		long double	Rout;
		long double	R;
		long double	Cout;
		long double	G;
		long double	Vout_old;
};

#endif
