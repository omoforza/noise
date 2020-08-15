#include"cavity.h"
#include"electric_field.h"
#include"mirror.h"
#include"laser.h"
#include<iostream>
#include<cmath>

using std::cout;
using std::endl;

void cavity::Init()
{
	L = abs( M1.GetX() - M2.GetX() );
	//phase and amplitude of all fields are initially set to 0.0
	Eplus.SetA  (0.0);
	Eplus.SetPhi(0.0);
	Erefl.SetA  (0.0);
	Erefl.SetPhi(0.0);
	Einc.SetA   (0.0);
	Einc.SetPhi (0.0);
}

void cavity::GetNewEF(laser & las)
{
	las.GetField(Einc, M1.GetX(), TIME);
	cout << "OK!" << endl;
}
