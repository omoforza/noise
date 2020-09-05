#include"pdh.h"
#include"electric_field.h"
#include<fstream>
#include<iomanip>

using std::endl;
using std::ofstream;
using std::setprecision;

void pdh::ReflInt()
{
	cav.rampa(las);
	cav.reset();
}

void pdh::ChargeCavity()
{
	double b;
	b = las.GetBeta();	
	las.SetBeta(0.0);
	ofstream out;
	out.open("charge.txt");
	out << setprecision(16);
	electric_field ef;
	for(int i = 0; i < 10000; i++)
	{
		cav.GetNewEF(las);
		out << cav.GetTime() << "\t" << cav.GetIrefl() << endl;
	}
	out.close();
	cav.reset();
	las.SetBeta(b);
}
