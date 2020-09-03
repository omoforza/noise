#ifndef AMPA_H
#define AMPA_H

class AmpA
{
	public:
		//resistance and capacity value in Ohm and Fahrad
		AmpA(double r1 = 1000.0, double c1 = 100.0e-12):
			R1(r1), C1(c1)
		{
			V_old = 0.0;
		}
		~AmpA() {}

		double ampID(double, double);

	private:
		double R1;
		double C1;
		//previous output of the amplifier
		double V_old;
};

#endif
