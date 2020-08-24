#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include"a.h"
#include"b.h"
#include"c.h"
#include"f.h"
class amplifier
{
	public:
		amplifier(double g) : G(g) {}
		double amp(double, double);
	private:
		//gain of the singles op-amp
		double G;

};

#endif
