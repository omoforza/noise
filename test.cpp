#include"pdh.h"

int main()
{

pdh p;
//da 500 a 10000 (oscilla)
//p.ReflIntDynamic(20000.0e6);
//p.ReflIntDynamicB(500.0e6);

//p.ReflIntStatic();

//if true the cavity is charged at resonance
p.ChargeCavity(true);

//p.Sim(true);
//p.ErrorSignal(1500.0e6);
//p.ErrorStatic();

return 0;
}
