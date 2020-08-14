#ifndef CAVITY_H
#define CAVITY_H

#include"mirror.h"

class cavity
{
	public:
		//a cavity is defined by two mirrors
		cavity(mirror m1, mirror m2) : M1(m1), M2(m2)
		{
			Init();
		}
	private:
		//class initialization function
		void Init();
		mirror M1;
		mirror M2;
		//cavity length L is defined as the distance between
		//the two mirror M1 and M2
		double L;
};

#endif
