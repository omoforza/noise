#include"cavity.h"
#include"mirror.h"
#include"electric_field.h"
#include"laser.h"
#include<iostream>
#include<cmath>

using std::endl;
using std::cout;

int main()
{

const double PI = acos(-1.0);	

laser las;

//mirror * m1 = (double r = 0.5, double phir = 0.0, double at = 0.0, 
//double ar = 0.0, double t = 0.5, double phit = 0.0, double x = 0.0)
mirror m1{0.99, PI, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 0.1};
mirror m2{0.99, PI, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 1.1};

//creazione della cavità
cavity * cav = new cavity(m1,m2);

cav->GetNewEF(las);

return 0;
}
