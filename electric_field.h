//Definition of the electric field

#ifndef HPF_H
#define HPF_H

class electric_field
{
	public:
		electric_field(double a = 1.0, double phi = 0.0,
				double freq = 100.0) :
			A(a), PHI(phi), FREQ(freq)
		{

		}

		double Intensity();



		



	private:
		double A;
		double PHI;
		double FREQ;

}

#endif
