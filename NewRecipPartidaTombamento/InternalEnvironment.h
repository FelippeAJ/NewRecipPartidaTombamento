#ifndef INTERNALENVIRONMENT_H
#define INTERNALENVIRONMENT_H

#include "Input.h"
#include "Refrigerant.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

class InternalEnvironment
{
public:
	InternalEnvironment();

	void calcProperties(double internalEnvironmentTemp, double sucLinePressure);
	void calcEnthalpyFluxToSuctionMuffler(double leakLoses, double massFlowDischarged, double directSuctionFactor);
	void calcEnthalpyFluxToCylinder(double leakMassSumBackFlow, double frequency);
	
	double getEnthalpyFluxToSuctionMuffler();
	double getEnthalpyFluxToCylinder();

	Refrigerant refrigerant;
	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;

protected:
	double enthalpyFluxToSuctionMuffler;
	double enthalpyFluxToCylinder;
};

#endif