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
		/*
		AmpA AA{1000.0,820.0e-12};
		AmpB BB{333.0,6.7e3,0.5,4.7e3,3.0e-12,G};
		AmpC CC{4.7e3,4.7e3,0.5,4.7e3,3.0e-12,1.2e-9,G};
		AmpC DD{4.7e3,4.7e3,0.5,22.0e3,3.0e-12,1.2e-9,G};
		AmpC EE{22.0e3,22.0e3,0.5,1.0/(1.0/4.7e3+1.0/1.0e6),3.0e-12,1.2e-9,G};
		AmpF FF{4.7e3,5.6,1.0e6,0.5,1000.0,3.0e-12,1.0e-6,G};
		AmpB GG{1000.0,1000.0,0.5,4.7e3,3.0e-12,G};
		*/
		AmpA AA{1.0e3L,9.0e-9L};
                AmpB BB{1000.0L,22.0e3L,0.5L,4.7e3L,3.0e-12L,G};
                AmpC CC{4.7e3L,4.7e3L,0.5L,4.7e3L,3.0e-12L, 4.7e-9L,G};
                AmpC DD{4.7e3L,4.7e3L,0.5L,22.0e3L,3.0e-12L,5.6e-9L,G};
                AmpC EE{22.0e3L,22.0e3L,0.5L,1.0L/(1.0L/4.7e3L+1.0L/1.0e6L),3.0e-12L,2.2e-9L,G};
                AmpF FF{4.7e3L,4.0L,1.0e6L,0.5L,1000.0L,3.0e-12L,1.0e-6L,G};
                AmpB GG{1000.0L,1000.0L,0.5L,4.7e3L,3.0e-12L,G};

};

#endif
