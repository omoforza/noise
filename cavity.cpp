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

void cavity::AssignLaser(laser & las)
{
	D0 = M1.GetX() - las.GetX();
}

void cavity::GetNewEF(laser & las)
{
	//The new Einc field is defined on the outer layer of
	//the first mirror
	Einc = las.GetField((M1.GetX()-las.GetX()) - D0, TIME);
	cout << "Einc cav : "<< Einc << endl;

	//eplus
	etemp = M2.reflect(Eplus);
	cout << "EincTr   : "<< M1.transmit(Einc) << endl;
	Eplus = M1.transmit(Einc) + M1.reflect(etemp);

	//Using Einc it is possible to define Erefl using the
	//properties of the mirror
	Erefl = M1.reflect(Einc) + M1.transmit(etemp);

	//update of the time variable
	TIME = TIME + 2.0*L/C;
}
