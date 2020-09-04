#include"cavity.h"
#include"mirror.h"
#include"electric_field.h"
#include"laser.h"
#include"hpf.h"
#include"amplifier.h"
#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>

using std::endl;
using std::cout;
using std::ofstream;
using std::setprecision;

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
hpf h1;
//attuatore piezoelettrico laser
AmpA pz{50.0,1.0e-9};
ofstream out;
out.open("data.txt");
out << setprecision(16);


double time;
double dt;
double intensity;
double temp = 0.0;
electric_field ef;

double fsr = C/(2.0*cav.GetL());
double fres = round(las.GetFreq() / fsr)*fsr;
double freq0 = las.GetFreq();

las.SetFreq(fres);

amplifier Ampl{600.0e3};
for(int i=0; i<1000000; i++)
{
	cav.GetNewEF(las);
	ef = cav.GetErefl();
	time = cav.GetTime();
	dt = cav.GetDT();
	out << time << "\t";
	intensity = ef.Intensity();
	out << intensity << "\t";
	intensity = ef.Intensity();
	temp = h1.filter(intensity,dt);
	temp = temp*sin(las.GetOmegaM()*time + PI*0.5);
	temp = Ampl.ampID(temp, dt);
	out << temp << "\t";
	temp = temp*10.0e3;
	las.ErrSig(temp);
	out << temp << endl;


}	
out.close();

return 0;
}
