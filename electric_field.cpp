#include"electric_field.h"
#include<complex>
#include<iostream>

using std::complex;
using std::polar;
using std::ostream;

//evaluate the field intensity. the output is simply the squared value of
//the amplitude
double electric_field::Intensity()
{
	return A*A;
}


//overloading of the + operator
electric_field operator + (const electric_field &  ef1,
                                const electric_field & ef2)
{
	complex<double> sum;
	sum = polar(ef1.A, ef1.PHI) + polar(ef2.A + ef2.PHI);
	electric_field esum{abs(sum),arg(sum)};
	return esum;
}


ostream & operator <<(ostream & out, electric_field & ef)
{
	out << "A = " << ef.GetA() << "; PHI = " << ef.GetPhi() ;
	return out;
}
