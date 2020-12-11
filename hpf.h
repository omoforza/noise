#ifndef HPF_H
#define HPF_H

class hpf
{
	public:
		hpf(
		long double r = 10.0e3, 
		long double l = 30.0e-3
		):
		R(r),L(l)
		{
			V_old = 0.0;
			I_old = 0.0;
			Vin   = 0.0;
		}

		//this function act as an high pass filter
		//on the intensity current signal from the photodiode
		long double filter(long double, long double);
		void reset()
		{
			V_old = 0.0;
                        I_old = 0.0;
                        Vin   = 0.0;
		}
	private:
		long double L;
		long double R;
		long double Vin;
		long double I_old;
		long double V_old;
};
#endif
