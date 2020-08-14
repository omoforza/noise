#include"laser.h"
#include"electric_field.h"

void laser::GenEF(electric_field & ef)
{
	ef.SetFreq(FREQ);
	ef.SetX(X);
}
