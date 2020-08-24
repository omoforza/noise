#ifndef F_H
#define F_H

class f
{
	public:
		f(double R1 = 4.7e3, double R2 = 5.6, double R3 = 1.0e6,
		double R = 0.5, double Rout = 1000.0, 
		double Cout = 3.0e-12, double C1 = 1.0e-6, 
		double G = 600.0e3)

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
