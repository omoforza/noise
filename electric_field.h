//Definition of the electric field probe fixed in space

#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

class electric_field
{
	public:
		//A and PHI are the field amplitude and phase
		//|A|exp(i(PHI))
		//freq is the frequenciy in Hz
		//x is the position relative to the origin in meters
		//t is time 
		electric_field(double a = 1.0, double phi = 0.0,
				double freq = 100.0, double x, double t) :
			A(a), PHI(phi), FREQ(freq)
		{

		}
		
		~electric_field() {}

		electric_field (electric_field & ef)
		{
			double A	= ef.A;
			double PHI	= ef.PHI;
			double FREQ 	= ef.FREQ;
			double RE 	= ef.RE;
			double IM 	= ef.IM;
		}
		
		double GetA()	{return A};
		double GetPhi()	{return PHI};

		void SetA(double a)	{A = a};
		void SetPhi(double phi)	{PHI = phi};

		double Intensity();

	private:
		double A;
		double PHI;
		double FREQ;
		double RE;
		double IM;
}

#endif
