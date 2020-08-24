#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include"a.h"
#include"b.h"
#include"c.h"
#include"f.h"
#include<iostream>
using std::cout;
using std::endl;
class amplifier
{
	public:
		amplifier(double g) : G(g) {}
		double Amp(double, double);
		void test() {cout << "TEST" << endl;}
	private:
		//gain of the singles op-amp
		double G;

};

#endif
