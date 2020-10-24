#include"pdh.h"

int main()
{

pdh p;
//da 500 a 10000 (oscilla)
//p.ReflIntDynamic(500.0e6);
//p.ReflIntDynamicB(500.0e6);

//p.ReflIntStatic();

//if true the cavity is charged at resonance
//p.ChargeCavity(true);

p.Sim(false);
//p.ErrorSignal(500.0e6);
//p.ErrorStatic();

return 0;
}
