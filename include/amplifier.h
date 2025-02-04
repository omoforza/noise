#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include"AmpA.h"
#include"AmpB.h"
#include"AmpC.h"
#include"AmpF.h"
#include<iostream>
#include<fstream>
using std::cout;
using std::endl;
using std::ofstream;
class amplifier
{
	public:
		amplifier(long double g) : G(g) {}


		long double amp  (long double, long double, bool);
		long double ampID(long double, long double, bool, bool, ofstream &);

		//low-pass filter stage only
		long double LP(long double, long double);

		//the RESET function set to the default values all 
		//internal tensions and parameters
		void RESET();
	private:
		//gain of the singles op-amp
		long double G;
		AmpA AA{4.0e3L,2.0e-9L};
                AmpB BB{4400.0L,22.0e3L,0.5L,4.7e3L,3.0e-12L,G};
                AmpC CC{4.7e3L,4.7e3L,0.5L,4.7e3L,3.0e-12L, 20.0e-9L,G};
                AmpC DD{4.7e3L,4.7e3L,0.5L,22.0e3L,3.0e-12L,20.0e-9L,G};
                AmpC EE{22.0e3L,22.0e3L,0.5L,1.0L/(1.0L/4.7e3L+1.0L/1.0e6L),3.0e-12L,20.0e-9L,G};
                AmpF FF{4.7e3L,4.0L,1.0e6L,0.5L,1000.0L,3.0e-12L,1.0e-6L,G};
                AmpB GG{1000.0L,1000.0L,0.5L,4.7e3L,3.0e-12L,G};

};

#endif
