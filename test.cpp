#include"cavity.h"
#include"mirror.h"
#include"electric_field.h"
#include"laser.h"
#include<iostream>

using std::endl;
using std::cout;

int main()
{

laser * las = new laser();
electric_field ef;
//mirror * m1 = (double r = 0.5, double phir = 0.0, double at = 0.0, 
//double ar = 0.0, double t = 0.5, double phit = 0.0, double x = 0.0)
mirror * m1 = (0.99, 0.0, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 0.1);
mirror * m2 = (0.99, 0.0, 0.0, 0.0, sqrt(1.0-0.99*0.99), 0.0, 1.1);

//creazione della cavità
cavity * cav = new cavity(m1,m2);

cavity->Accept(ef);


las->GenEF(ef);

cout << ef.GetA() << endl;

return 0;
}
