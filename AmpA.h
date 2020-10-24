#ifndef AMPA_H
#define AMPA_H

class AmpA
{
	public:
		//resistance and capacity value in Ohm and Fahrad
		AmpA(
		long double r1 = 1000.0,
		long double c1 = 100.0e-12
		):
			R1(r1), C1(c1)
		{
			V_old = 0.0;
		}
		~AmpA() {}

		long double amp  (long double, long double);
		long double ampID(long double, long double);

		//RESET function set all parameters to the initial value
		void RESET();

	private:
		long double R1;
		long double C1;
		//previous output of the amplifier
		long double V_old;
};

#endif
