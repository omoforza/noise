#include"mirror.h"
#include"electric_field.h"
#include<cmath>
#include<iostream>
using std::cout;
using std::endl;

electric_field mirror::reflect(electric_field ef)
{
	electric_field er;
	er.SetA(ef.GetA()*R);	
	er.SetPhi(ef.GetPhi() + PHIR);
	return er;
}

electric_field mirror::ex_reflect(electric_field ef)
{
	electric_field er;
	er.SetA(ef.GetA()*R);	
	er.SetPhi(ef.GetPhi());
	return er;
}

electric_field mirror::transmit(electric_field ef)
{
	electric_field et;
	long double t_int;
	t_int = ef.GetA()*T*sqrt(1.0L-AT);
	et.SetA(t_int);	
	et.SetPhi(ef.GetPhi());	
	return et;
}
