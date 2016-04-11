#ifndef MOTOR_H
#define MOTOR_H

#include "Input.h"
#include "Interpolation.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

class Motor
{
public:
	Motor();
	void calcEfficiency(double axisPotency);
	void calcHeat(double consumption);
	void setCoef(vector<double> coeficientsValue);
	
	double getCoeficients(int id);
	double getEfficiency(); 
	double getHeat();

	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;

protected:
	vector<double> coeficients;
	double efficiency;
	double heat;
	Interpolation interp;
};

#endif

