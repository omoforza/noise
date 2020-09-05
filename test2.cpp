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

cav.GetNewEF(las);
cav.GetNewEF(las);
cav.GetNewEF(las);
cav.GetNewEF(las);
cav.GetNewEF(las);
electric_field ef;
ef = cav.GetEinc();
cout << "Real part = " << ef.GetRe() << ";	Imag part = "<< ef.GetIm() << endl;
double phi = ef.GetPhi();
ef.SetPhi(phi + PI);
cout << "Real part = " << ef.GetRe() << ";	Imag part = "<< ef.GetIm() << endl;

return 0;
}
