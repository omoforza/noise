#include"cavity.h"
#include"electric_field.h"
#include"mirror.h"
#include<cmath>

void cavity::Init()
{
	L = abs( M1.GetX() - M2.GetX() );
}

void cavity::GetNewEF(laser &)
{
	
}
