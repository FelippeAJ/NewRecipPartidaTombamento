#ifndef HEATTRANSFERRATE_H
#define HEATTRANSFERRATE_H

#include <iostream>

class HeatTransferRate
{
public:
	HeatTransferRate();
	void calcHeatTransferRate(double UA, double temperatureOne, double temperature2);
	double getHeatTransferRate();

protected:
	double heatTransferRate;
};

#endif