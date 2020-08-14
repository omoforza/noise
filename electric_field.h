//Definition of the electric field probe fixed in space

#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

class electric_field
{
	public:
		electric_field(double a = 1.0, double phi = 0.0,
				double freq = 100.0) :
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

		double Intensity();

	private:
		double A;
		double PHI;
		double FREQ;
		double RE;
		double IM;
}

#endif
