#include"cavity.h"
#include"mirror.h"
#include<cmath>

void cavity::Init()
{
	L = abs( M1.GetX() - M2.GetX() );
}
