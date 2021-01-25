#include"pdh.h"

int main()
{

pdh p;

//if true the cavity is charged at resonance
//p.ChargeCavity(true);


//da 500 a 10000 (oscilla)
p.ReflIntDynamic(14320.0e6);
//p.ReflIntStatic();

//p.ErrorSignal(500.0e6);
//p.ErrorStatic();
//p.ErrorEvolution();


//p.Sim(false);

return 0;
}
