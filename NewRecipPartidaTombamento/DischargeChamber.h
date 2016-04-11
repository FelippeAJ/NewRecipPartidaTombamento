#ifndef DISCHARGECHAMBER_H
#define DISCHARGECHAMBER_H

#include "Input.h"
#include "Refrigerant.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

class DischargeChamber
{
public:
	DischargeChamber();

	void calcProperties(double condesationTemp, double disChamberTemp);
	void calcEnthalpyFluxToDischargeMuffler(double massFlowDischarged);
	void calcEnthalpyFluxToCylinder(double massSumBackflow, double frequency);
	
	double getEnthalpyFluxToDischargeMuffler();
	double getEnthalpyFluxToCylinder();

	Refrigerant refrigerant;
	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;

protected:

	double enthalpyFluxToDischargeMuffler;
	double enthalpyFluxToCylinder;	
};

#endif