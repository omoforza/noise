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

electric_field ef;
double ir;
double ip;
double time;
ofstream file;
file.open("data.txt");
for(int i=0; i<1000; i++)
{
	cav.GetNewEF(las);
	ef = cav.GetErefl();
	ir = ef.Intensity();
	ef = cav.GetEplus();
	ip = ef.Intensity();
	time = cav.GetTime();
	file << ir << "\t" << ip << "\t" << time << endl;
}
file.close();

cout << ef<< endl;

return 0;
}
