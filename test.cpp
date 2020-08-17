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


electric_field e1, e2, esum;

e1.SetA(1.0);
e1.SetPhi(0.0);
e2.SetA(1.0);
e2.SetPhi(PI*0.5);

esum = e1 + e2;

cout << e1 << endl;
cout << e2 << endl;
cout << esum << endl;
cout << esum.Intensity() << endl;


return 0;
}
