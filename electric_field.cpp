#include"electric_field.h"

//evaluate the field intensity. the output is simply the squared value of
//the amplitude
double electric_field::Intensity()
{
	return A*A;
}
