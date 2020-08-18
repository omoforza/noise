#include"mirror.h"
#include"electric_field.h"
#include<cmath>

electric_field mirror::reflect(electric_field ef)
{
	electric_field er;
	er.SetA(ef.GetA()*R*(-1.0));	
	return er;
}

electric_field mirror::transmit(electric_field ef)
{
	electric_field et;
	et.SetA(ef.GetA()*T*sqrt(AT));	
	return et;
}
