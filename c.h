#ifndef C_H
#define C_H

class c
{
	public:
		c(double R1 = 4.7e3, double R2 = 4.7e3, double R = 0.5, double Rout = 4.7e3, double Cout = 3.0e-12, double C1 = 5.6e-9, double G = 600.0e3)

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
