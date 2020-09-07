#include"amplifier.h"
#include"AmpA.h"
#include"AmpB.h"
#include"AmpC.h"
#include"AmpF.h"
#include<iostream>

using std::cout;
using std::endl;

double amplifier::amp(double Vin, double dt, bool ind)
{

//linking op-amp cables
double vtemp = 0.0;

vtemp = AA.ampID(Vin,dt);
vtemp = BB.amp(vtemp,dt);
if(ind){
vtemp = CC.amp(vtemp,dt);
vtemp = DD.amp(vtemp,dt);
vtemp = EE.amp(vtemp,dt);
vtemp = FF.amp(vtemp,dt);
vtemp = GG.amp(vtemp,dt);
}
return vtemp;
}


double amplifier::ampID(double Vin, double dt, bool ind)
{
//linking op-amp cables
double vtemp = 0.0;

vtemp = AA.ampID(Vin,dt);
vtemp = BB.ampID(vtemp,dt);
//integrator op-amp
if(ind){
vtemp = CC.ampID(vtemp,dt);
vtemp = DD.ampID(vtemp,dt);
vtemp = EE.ampID(vtemp,dt);
vtemp = FF.ampID(vtemp,dt);
vtemp = GG.ampID(vtemp,dt);
}
return vtemp;
}
