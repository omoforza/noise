//Definition of the electric field probe fixed in space

#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

class electric_field
{
	public:
		//A and PHI are the field amplitude and phase
		//|A|exp(i(PHI))
		electric_field(double a = 0.0, double phi = 0.0) :
			A(a), PHI(phi)
		{

		}
		
		~electric_field() {}

		electric_field (electric_field & ef)
		{
			double A	= ef.A;
			double PHI	= ef.PHI;
		}
		
		double GetA()	{return A;}
		double GetPhi()	{return PHI;}

		void SetA(double a)		{A = a;}
		void SetPhi(double phi)		{PHI = phi;}

		double Intensity();

	private:
		double A;
		double PHI;
};

#endif
