#ifndef OIL_H
#define OIL_H

#include <cmath>
#include "POLOIO.h"

class Oil
{
public:
	Oil();

	void calcViscosity(double temperatureValue);

	double getViscosityCoef1();
	double getViscosityCoef2();
	double getViscosityCoef3();
	double getViscosity();

	double expTemp;

protected:
	double viscosity;
	double viscosityCoef1;
	double viscosityCoef2;
	double viscosityCoef3;

	
};

#endif

