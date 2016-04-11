#ifndef EVAPORATOR_H
#define EVAPORATOR_H

#include "Input.h"
#include "Refrigerant.h"

class Evaporator
{
public:
	Evaporator();

	void calcEnthlapyDiference(double subcoolingTemp, double superHeatingTemp, double evaporationTemp);

	double getEnthalpyDiference();

protected:
	double enthlapyDiference;
	Refrigerant refrigerant;

};

#endif