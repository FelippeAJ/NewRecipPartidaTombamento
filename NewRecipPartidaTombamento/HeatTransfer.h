#ifndef HEATTRANSFER_H
#define HEATTRANSFER_H

#include "Input.h"
#include "Constants.h"
#include "AdimensionalNumbers.h"

class HeatTransfer
{
public:
	HeatTransfer();

	void calcArea(double deadVolValue, double cylBoreValue, double supDeadPoint, double mechanismPosition, double cylArea);
	void calcConvectionCoef(double NusseltValue, double thermalConductValue, double cylBoreValue);

	double getArea();
	double getConvectionCoef();

protected:
	static double area;
	static double convectionCoeficient;
};

#endif