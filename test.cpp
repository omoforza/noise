#include"pdh.h"

int main()
{

pdh p;

//if true the cavity is charged at resonance
//p.ChargeCavity(true);


//da 500 a 10000 (oscilla)
//p.ReflIntDynamic(14320.0e6);
//p.ReflIntStatic();

//p.ErrorSignal(1.913e10);
//p.ErrorStatic();
//p.ErrorEvolution();


p.Sim(true);

return 0;
}
