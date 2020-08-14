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

las->GenEF(ef);

cout << ef.GetA() << endl;

return 0;
}
