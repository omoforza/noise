#include"mirror.h"
#include"electric_field.h"
#include<cmath>

electric_field mirror::reflect(electric_field ef)
{
	ef.SetA(ef.GetA()*R*sqrt(AR));	
	ef.SetPhi(ef.GetPhi() + PHIR);	
	return ef;
}

electric_field mirror::transmit(electric_field ef)
{
	ef.SetA(ef.GetA()*T*sqrt(AT));	
	ef.SetPhi(ef.GetPhi() + PHIR);	
	return ef;
}
