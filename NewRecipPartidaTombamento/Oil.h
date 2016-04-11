#ifndef OIL_H
#define OIL_H

#include <cmath>
#include "Input.h"

class Oil
{
public:
	Oil();

	void calcViscosity(double temperatureValue);

	void setViscosityCoef1(double viscosityCoef1Value);
	void setViscosityCoef2(double viscosityCoef2Value);
	void setViscosityCoef3(double viscosityCoef3Value); 

	double getViscosityCoef1();
	double getViscosityCoef2();
	double getViscosityCoef3();
	double getViscosity();

protected:
	double viscosity;
	double viscosityCoef1;
	double viscosityCoef2;
	double viscosityCoef3;
};

#endif

