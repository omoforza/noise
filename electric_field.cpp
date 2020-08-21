#include"electric_field.h"
#include<complex>
#include<iostream>

using std::complex;
using std::polar;
using std::ostream;
using std::endl;
using std::cout;

//evaluate the field intensity. the output is simply the squared value of
//the amplitude
double electric_field::Intensity()
{
	return A*A;
}


//overloading of the + operator
electric_field operator + (const electric_field & ef1, 
		const electric_field & ef2)
{
	electric_field esum;
	complex<double> sum;
	sum = polar(ef1.GetA(), ef1.GetPhi()) + 
		polar(ef2.GetA(), ef2.GetPhi());

	esum.SetA(abs(sum));
	esum.SetPhi(arg(sum));
	return esum;
}

//overloading of the - operator
electric_field operator - (const electric_field & ef1, 
		const electric_field & ef2)
{
	electric_field esum;
	complex<double> sum;
	sum = polar(ef1.GetA(), ef1.GetPhi()) - 
		polar(ef2.GetA(), ef2.GetPhi());

	esum.SetA(abs(sum));
	esum.SetPhi(arg(sum));
	return esum;
}


ostream & operator <<(ostream & out, electric_field ef)
{
	out << "A = " << ef.GetA() << "; PHI = " << ef.GetPhi() ;
	return out;
}
