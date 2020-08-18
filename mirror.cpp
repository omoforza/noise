#include"mirror.h"
#include"electric_field.h"
#include<cmath>
#include<iostream>
using std::cout;
using std::endl;

electric_field mirror::reflect(electric_field ef)
{
	electric_field er;
	er.SetA(ef.GetA()*R*(-1.0));	
	return er;
}

electric_field mirror::transmit(electric_field ef)
{
	electric_field et;
	double t_int;
	t_int = ef.GetA()*T*sqrt(1.0-AT);
	et.SetA(t_int);	
	return et;
}
