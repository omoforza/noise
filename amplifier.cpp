#include"amplifier.h"
#include"a.h"
#include"b.h"
#include"c.h"
#include"f.h"

double amplifier::Amp(double Vin, double dt)
{
//creation of all the components of the amplifier circuit

a ampA{1000.0,100.0e-12};
b ampB{333.0,6.7e3,0.5,4.7e3,3.0e-12,G};
c ampC{4.7e3,4.7e3,0.5,4.7e3,3.0e-12,5.6e-9,G};
c ampD{4.7e3,4.7e3,0.5,22.0e3,3.0e-12,5.6e-9,G};
c ampE{22.0e3,22.0e3,0.5,1.0/(1.0/4.7e3+1.0/1.0e6),3.0e-12,1.2e-9,G};
f ampF{4.7e3,5.6,1.0e6,0.5,1000.0,3.0e-12,1.0e-6,G};
b ampG{1000.0,1000.0,0.5,4.7e3,3.0e-12,G};


//linking op-amp cables
double vtemp = 0.0;
vtemp = ampA.amp(Vin,dt);
vtemp = ampB.amp(vtemp,dt);
vtemp = ampC.amp(vtemp,dt);
vtemp = ampD.amp(vtemp,dt);
vtemp = ampE.amp(vtemp,dt);
vtemp = ampF.amp(vtemp,dt);
vtemp = ampG.amp(vtemp,dt);

return vtemp;
}
