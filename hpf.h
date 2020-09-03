#ifndef HPF_H
#define HPF_H

class hpf
{
	public:
		hpf(
		double r = 10.0e3, 
		double l = 30.0e-3
		):
		R(r),L(l)
		{
			V_old = 0.0;
			I_old = 0.0;
			Vin   = 0.0;
		}

		//this function act as an high pass filter
		//on the intensity current signal from the photodiode
		double filter(double, double);
	private:
		double L;
		double R;
		double Vin;
		double I_old;
		double V_old;
};
#endif
