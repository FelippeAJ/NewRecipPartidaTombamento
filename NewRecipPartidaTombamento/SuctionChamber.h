#ifndef SUCTIONCHAMBER_H
#define SUCTIONCHAMBER_H

#include "Input.h"
#include "Refrigerant.h"

class SuctionChamber
{
public:
	SuctionChamber();

	void calcProperties(double evaporationTemp, double sucChamberTemp);
	void calcEnthalpyFluxToCylinder(double massSumFlux, double frequency);
	double getEnthalpyFluxToCylinder();

	Refrigerant refrigerant;

protected:

	double enthalpyFluxToCylinder;
	
};

#endif