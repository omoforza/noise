#ifndef AMPB_H
#define AMPB_H

class AmpB
{
	public:
		AmpB(
		double r1 = 333.0,
		double r2 = 6.7e3,
		double r = 0.01,
		double rout = 4.3e8,
		double cout = 3.0e-15,
		double g = 600.0e3
		):
		R1(r1), R2(r2), R(r), Rout(rout), Cout(cout), G(g)
		{
			Vout_old = 0.0;
		}

		//amplifier stage and IDeal implifier stage
		double amp (double, double);
		//ideal
		double ampID(double, double);

		//RESET function set all parameters to the initial value
                void RESET();


	private:
		double	R1;
		double	R2;
		double	Rout;
		double	R;
		double	Cout;
		double	G;
		double	Vout_old;
};

#endif
