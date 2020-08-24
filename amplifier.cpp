#include"amplifier.h"
#include"AmpA.h"
#include"AmpB.h"
#include"AmpC.h"
#include"AmpF.h"

double amplifier::Amp(double Vin, double dt)
{
//creation of all the components of the amplifier circuit

AmpA AA{1000.0,100.0e-12};
AmpB BB{333.0,6.7e3,0.5,4.7e3,3.0e-12,G};
AmpC CC{4.7e3,4.7e3,0.5,4.7e3,3.0e-12,5.6e-9,G};
AmpC DD{4.7e3,4.7e3,0.5,22.0e3,3.0e-12,5.6e-9,G};
AmpC EE{22.0e3,22.0e3,0.5,1.0/(1.0/4.7e3+1.0/1.0e6),3.0e-12,1.2e-9,G};
AmpF FF{4.7e3,5.6,1.0e6,0.5,1000.0,3.0e-12,1.0e-6,G};
AmpB GG{1000.0,1000.0,0.5,4.7e3,3.0e-12,G};


//linking op-amp cables
double vtemp = 0.0;
vtemp = AA.amp(Vin,dt);
vtemp = BB.amp(vtemp,dt);
vtemp = CC.amp(vtemp,dt);
vtemp = DD.amp(vtemp,dt);
vtemp = EE.amp(vtemp,dt);
vtemp = FF.amp(vtemp,dt);
vtemp = GG.amp(vtemp,dt);

return vtemp;
}
