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


electric_field ef1, ef2, sum;

ef1.SetA(1.0);
ef2.SetA(1.0);
ef1.SetPhi(0.0);
ef2.SetPhi(PI);

cout << ef1 <<"\t" << ef1.GetA() << "\t"<< ef1.GetPhi() << endl;
cout << ef2 << endl;
cout << sum << endl;

sum = ef1 + ef2;

cout << "dopo la somma"<< endl;
cout << ef1 << endl;
cout << ef2 << endl;
cout << sum << endl;





return 0;
}
