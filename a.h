#ifndef A_H
#define A_H

class a
{
	public:
		//resistance and capacity value in Ohm and Fahrad
		a(double r1 = 1000.0, double c1 = 100.0e-12):
			R1(r1), C1(c1)
		{
			V_old = 0.0;
		}
		~a() {}

		double amp(double, double);

	private:
		double R1;
		double C1;
		//previous output of the amplifier
		double V_old;
};

#endif
