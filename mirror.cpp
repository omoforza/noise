#include"mirror.h"
#include"electric_field.h"

void mirror::reflect(electric_field & ef)
{
	ef.SetA(ef.GetA()*R*sqrt(AR));	
	ef.SetPhi(ef.GetPhi() + PHIR);	
}

void mirror::transmit(electric_field & ef)
{
	ef.SetA(ef.GetA()*T*sqrt(AT));	
	ef.SetPhi(ef.GetPhi() + PHIR);	
}
