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
		amplifier(double g) : G(g) {}


		double amp  (double, double, bool);
		double ampID(double, double, bool, bool, ofstream &);

		//low-pass filter stage only
		double LP(double, double);

		//the RESET function set to the default values all 
		//internal tensions and parameters
		void RESET();
	private:
		//gain of the singles op-amp
		double G;
		AmpA AA{1000.0,820.0e-12};
		AmpB BB{333.0,6.7e3,0.5,4.7e3,3.0e-12,G};
		AmpC CC{4.7e3,4.7e3,0.5,4.7e3,3.0e-12,1.2e-9,G};
		AmpC DD{4.7e3,4.7e3,0.5,22.0e3,3.0e-12,1.2e-9,G};
		AmpC EE{22.0e3,22.0e3,0.5,1.0/(1.0/4.7e3+1.0/1.0e6),3.0e-12,1.2e-9,G};
		AmpF FF{4.7e3,5.6,1.0e6,0.5,1000.0,3.0e-12,1.0e-6,G};
		AmpB GG{1000.0,1000.0,0.5,4.7e3,3.0e-12,G};


};

#endif
