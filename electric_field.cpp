#include"electric_field.h"
#include<complex>

using std::complex;
using std::polar;

//evaluate the field intensity. the output is simply the squared value of
//the amplitude
double electric_field::Intensity()
{
	return A*A;
}


electric_field operator + (const electric_field &  ef1,
                                const electric_field & ef2)
{
	complex<double> sum;
	sum = polar(ef1.A, ef1.PHI) + polar(ef2.A + ef2.PHI);
	electric_field esum{abs(sum),arg(sum)};
	return esum;
}
