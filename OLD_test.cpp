#include"cavity.h"
#include"mirror.h"
#include"electric_field.h"
#include"laser.h"
#include<iostream>
#include<cmath>
#include<fstream>

using std::endl;
using std::cout;
using std::ofstream;

int main()
{

const double PI = acos(-1.0);	

laser las;

//mirror * m1 = (double r = 0.5, double phir = 0.0, double at = 0.0, 
//double ar = 0.0, double t = 0.5, double phit = 0.0, double x = 0.0)
mirror m1{0.99, PI, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 0.1};
mirror m2{0.99, PI, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 1.1};

//creazione della cavità
cavity cav{m1,m2};
cav.AssignLaser(las);

/*
ofstream out;
out.open("data.txt");
double time;
double intensity;
electric_field ef;
for(int i=0; i<10; i++)
{
	cav.GetNewEF(las);
	ef = cav.GetEplus();
	intensity = ef.Intensity();
	time = cav.GetTime();
	out << time << "\t" << intensity << endl;
}	
out.close();
*/

//test di Intensity

electric_field ef1;
electric_field ef2;
electric_field esum;

ef1.SetA(1.0);
ef2.SetA(1.0);
ef1.SetPhi(0.0);
ef2.SetPhi(PI);

esum = ef1 + ef2;

double int1 = esum.Intensity();

cout << "ef1  : " << ef1 << endl;
cout << "ef2  : " << ef2 << endl;
cout << "esum : " << esum << endl;
cout << "int1 : " << int1 << endl;

return 0;
}
