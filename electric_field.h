//Definition of the electric field probe fixed in space

#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

#include<iostream>
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
		}
		
		double GetA() const	{return A;} 
		double GetPhi() const	{return PHI;}

		void SetA(double a)		{A = a;}
		void SetPhi(double phi)		{PHI = phi;}

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
};

#endif
