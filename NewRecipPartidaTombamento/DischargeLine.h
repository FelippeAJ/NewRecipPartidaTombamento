#ifndef DISCHARGELINE_H
#define DISCHARGELINE_H

#include "Input.h"
#include "Refrigerant.h"

class DischargeLine
{
public:
	DischargeLine();

	void calcProperties(double condesationTemp, double disLineTemp);
	void calcEnthalpyFluxToOutlet(double massFlowDischarged);
	double getEnthalpyFluxToOutlet();

	Refrigerant refrigerant;

protected:
	double enthalpyFluxToOutlet;

};

#endif