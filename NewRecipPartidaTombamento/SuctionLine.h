#ifndef SUCTIONLINE_H
#define SUCTIONLINE_H

#include "Input.h"
#include "Refrigerant.h"

class SuctionLine
{
public:
	SuctionLine();

	void calcProperties(double evaporationTemp, double sucLineTemp);
	void calcEnthalpyFluxtoSuctionMuffler(double massFlowDischarged, double directSuctionFactor);
	void calcEnthalpyFluxtoInternalEnvironment(double massFlowDischarged);

	double getEnthalpyFluxtoSuctionMuffler();
	double getEnthalpyFluxtoInternalEnvironment();

	Refrigerant refrigerant;

protected:
	double enthalpyFluxtoSuctionMuffler;
	double enthalpyFluxtoInternalEnvironment;
};

#endif