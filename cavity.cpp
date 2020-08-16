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
	//The new Einc field is defined on the outer layer of
	//the first mirror
	las.GetField(Einc, M1.GetX() - las.GetX(), TIME);
	//Using Einc it is possible to define Erefl using the
	//properties of the mirror
	Erefl = M1.reflect(Einc);


	cout << "L = " << L << endl;
	cout << "Einc:  A  = " << Einc.GetA() << endl;
	cout << "Einc:  Phi= " << Einc.GetPhi() << endl;
	cout << "Erefl: A  = " << Erefl.GetA() << endl;
	cout << "Erefl: Phi= " << Erefl.GetPhi() << endl;
	cout << "M1: Phir =  " << M1.GetPhir() << endl;


}
