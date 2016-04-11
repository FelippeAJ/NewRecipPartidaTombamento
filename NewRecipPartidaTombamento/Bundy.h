#ifndef BUNDY_H
#define BUNDY_H

#include <iostream>
#include "Input.h"
#include "Refrigerant.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

using namespace std;

class  Bundy
{
public:
	Bundy();

	void calcProperties(double condensingTemperature, double dischargeMufflerTemp);
	void calcEnthalpyFluxToDischargeLine(double massFlowDischarged);
	void calcBundyAverageTemp(double dischargeMufflerTemp, double dischargeLineTemp);

	double getEnthalpyFluxToDischargeLine();
	double getBundyAverageTemp();

	Refrigerant refrigerant;
	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;

protected:
	double enthalpyFluxToDischargeLine;
	double bundyAverageTemp;
};

#endif