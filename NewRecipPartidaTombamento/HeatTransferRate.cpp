#include "HeatTransferRate.h"

HeatTransferRate::HeatTransferRate()
{

}

void HeatTransferRate::calcHeatTransferRate(double UA, double temperatureOne, double temperatureTwo)
{
	heatTransferRate = UA*(temperatureOne - temperatureTwo);
}

double HeatTransferRate::getHeatTransferRate()
{
	return heatTransferRate;
}