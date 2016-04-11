#ifndef GLOBALHEATTRANSFER_H
#define GLOBALHEATTRANSFER_H

#include "Input.h"
#include <numeric>
#include<stdarg.h>
#include <vector>

class GlobalHeatTransfer
{
public:
	GlobalHeatTransfer();
	void calcUA(double temperatureOne, double temperatureTwo);
	void calcInputEnergyRateSum(int n, ...);
	void calcOutputEnergyRateSum(int n, ...);
	
	double getUA();
	double getInputEnergyRateSum();
	double getOutputEnergyRateSum();

	void setInputEnergyRateSum(double inputEnergyRateSumValue);
	void setOutputEnergyRateSum(double outputEnergyRateSumValue);
	
protected:
	double UA;
	double inputEnergyRateSum;
	double outputEnergyRateSum;
};

#endif
