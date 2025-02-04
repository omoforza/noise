//Definition of the electric field probe fixed in space

#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

#include<iostream>
#include<complex>
using std::ostream;
using std::complex;
using std::polar;
using std::real;
using std::imag;

class electric_field
{
	public:
		//A and PHI are the field amplitude and phase
		//|A|exp(i(PHI))
		electric_field(long double a=0.0L, long double phi=0.0L) :
			A(a), PHI(phi)
		{
			E_C	= polar(A,PHI);
			E_RE	= E_C.real();
			E_IM	= E_C.imag();
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
		
		long double GetA() const	{return A;} 
		long double GetPhi() const	{return PHI;}

		long double GetRe() const	{return E_RE;}
		long double GetIm() const	{return E_IM;}

		void SetA(long double a)
		{
			A = a;
			E_C	= polar(A,PHI);
			E_RE	= E_C.real();
			E_IM	= E_C.imag();
		}
		void SetPhi(long double phi)		
		{
			PHI = phi;
			E_C	= polar(A,PHI);
			E_RE	= E_C.real();
			E_IM	= E_C.imag();
		}

		long double Intensity();

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
		long double A;
		long double PHI;
		complex<long double> E_C;
		long double E_RE;
		long double E_IM;
};

#endif
