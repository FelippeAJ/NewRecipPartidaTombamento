#ifndef ADIMENSIONALNUMBERS_H
#define ADIMENSIONALNUMBERS_H

#include <iostream>
#include <cmath>
#include "Input.h"

using namespace std;

class AdimensionalNumbers
{
public:
	AdimensionalNumbers();

	void calcReynolds(double rhoValue, double velValue, double caractLengthValue, double viscosValue);
	void calcPrandt(double viscosValue,double cpValue, double thermalConductValue);
	void calcNusselt();

	double getReynolds();
	double getNusselt();
	double getPrandt();

protected:
	static double Reynolds;
	static double Prandt;
	static double Nusselt;
};

#endif