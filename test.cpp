#include"cavity.h"
#include"mirror.h"
#include"electric_field.h"
#include"laser.h"
#include"amplifier.h"
#include<iostream>
#include<cmath>
#include<fstream>

using std::endl;
using std::cout;
using std::ofstream;

int main()
{

const double PI = acos(-1.0);	
const double C = 299792458.0;

laser las;

//mirror * m1 = (double r = 0.5, double phir = 0.0, double at = 0.0, 
//double ar = 0.0, double t = 0.5, double phit = 0.0, double x = 0.0)
mirror m1{0.99, PI, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 0.1};
mirror m2{0.99, PI, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 1.1};


//creazione della cavità
cavity cav{m1,m2};
cav.AssignLaser(las);
ofstream out;
out.open("data.txt");


double time;
double dt;
double intensity;
double amp_int;
electric_field ef;

double fsr = C/(2.0*cav.GetL());
double fres = round(las.GetFreq() / fsr)*fsr;
double freq0 = las.GetFreq();

las.SetFreq(freq0);

amplifier Ampl{600.0e3};
for(int i=0; i<1000; i++)
{
	cav.GetNewEF(las);
	ef = cav.GetErefl();
	intensity = ef.Intensity();
	time = cav.GetTime();
	dt = cav.GetDT();
	amp_int = Ampl.Amp(intensity, dt);
	out << time << "\t" << intensity << "\t" << amp_int << endl;
}	
out.close();

cav.rampa(las);

return 0;
}
