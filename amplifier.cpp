#include"amplifier.h"
#include"AmpA.h"
#include"AmpB.h"
#include"AmpC.h"
#include"AmpF.h"
#include<iostream>
#include<iomanip>
#include<fstream>

using std::cout;
using std::endl;
using std::ofstream;
using std::setprecision;

long double amplifier::amp(long double Vin, long double dt, bool ind)
{

//linking op-amp cables
long double vtemp = 0.0;

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


long double amplifier::ampID(long double Vin, long double dt, bool ind, bool WO, ofstream  & out)
{
//"amp_data.txt" contains the signal values after each amplification
//stage. It can be enabled or disabled (false) using the bool variable,
//(W)rite(O)utput WO.	

//linking op-amp cables
long double vtemp = 0.0;
if(WO){out<< Vin << "\t";}
vtemp = AA.ampID(Vin,dt);
if(WO){out<< vtemp << "\t";}
vtemp = BB.ampID(vtemp,dt);
if(WO){out<< vtemp << "\t";}
//integrator op-amp
if(ind){
vtemp = CC.ampID(vtemp,dt);
if(WO){out<< vtemp << "\t";}
vtemp = DD.ampID(vtemp,dt);
if(WO){out<< vtemp << "\t";}
vtemp = EE.ampID(vtemp,dt);
if(WO){out<< vtemp << "\t";}
vtemp = FF.ampID(vtemp,dt);
if(WO){out<< vtemp << "\t";}
vtemp = GG.ampID(vtemp,dt);
if(WO){out<< vtemp << endl;}
}
return vtemp;
}

long double amplifier::LP(long double Vin, long double dt){

	long double vtemp = 0.0;
	vtemp = AA.ampID(Vin,dt);
	return vtemp;

}

void amplifier::RESET(){
	AA.RESET();
	BB.RESET();
	CC.RESET();
	DD.RESET();
	EE.RESET();
	FF.RESET();
	GG.RESET();
}
