#ifndef DISCHARGEMUFFLER_H
#define DISCHARGEMUFFLER_H

#include "Refrigerant.h"
#include "Input.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

class DischargeMuffler
{
public:
	DischargeMuffler();

	void calcProperties(double condensingTemp, double dischargeMufflerTemperature);
	void calcEnthalpyFluxtoBundy(double massFlowDischarged);
	void calcDischargeMufflerAverageTemp(double dischargeChamberTemp, double dischargeMufflerTemp);
	
	double getEnthalpyFluxtoBundy();
	double getDischargeMufflerAverageTemp();

	Refrigerant refrigerant;
	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;

protected:
	double enthalpyFluxtoBundy;
	double dischargeMufflerAverageTemp;
};

#endif