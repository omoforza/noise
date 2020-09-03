#include"amplifier.h"
#include"AmpA.h"
#include"AmpB.h"
#include"AmpC.h"
#include"AmpF.h"
#include<iostream>

using std::cout;
using std::endl;

double amplifier::amp(double Vin, double dt)
{

//linking op-amp cables
double vtemp = 0.0;

vtemp = AA.amp(Vin,dt);
//cout << "Out A = " << vtemp << endl;
vtemp = BB.amp(vtemp,dt);
//cout << "Out B = " << vtemp << endl;
vtemp = CC.amp(vtemp,dt);
//cout << "Out C = " << vtemp << endl;
vtemp = DD.amp(vtemp,dt);
//cout << "Out D = " << vtemp << endl;
vtemp = EE.amp(vtemp,dt);
//cout << "Out E = " << vtemp << endl;
vtemp = FF.amp(vtemp,dt);
//cout << "Out F = " << vtemp << endl;
vtemp = GG.amp(vtemp,dt);
//cout << "Out G = " << vtemp << endl;
//cout << " " << endl;

return vtemp;
}
