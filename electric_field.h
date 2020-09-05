//Definition of the electric field probe fixed in space

#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

#include<iostream>
#include<complex>
using std::ostream;

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

		electric_field (const electric_field & ef)
		{
			A	= ef.A;
			PHI	= ef.PHI;
			E_C	= polar(ef.A,ef.PHI);
			E_RE	= E_C.real();
			E_IM	= E_C.imag();

		}
		
		double GetA() const	{return A;} 
		double GetPhi() const	{return PHI;}

		double GetRe() const	{return E_RE;}
		double GetIm() const	{return E_IM;}

		void SetA(double a)
		{
			A = a;
			E_C	= polar(A,PHI);
			E_RE	= E_C.real();
			E_IM	= E_C.imag();
		}
		void SetPhi(double phi)		
		{
			PHI = phi;
			E_C	= polar(A,PHI);
			E_RE	= E_C.real();
			E_IM	= E_C.imag();
		}

		double Intensity();

		//overloading of the + operator
		friend electric_field operator + 
			(const electric_field &, const electric_field &);

		//overloading of the - operator
		friend electric_field operator - 
			(const electric_field &, const electric_field &);

		//overloading of the << operator
		friend ostream & operator <<
			(ostream &, electric_field);

	private:
		double A;
		double PHI;
		complex<double> E_C
		double E_RE;
		double E_IM;
};

#endif
