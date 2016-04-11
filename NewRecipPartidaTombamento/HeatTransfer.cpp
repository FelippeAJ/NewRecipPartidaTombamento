#include "HeatTransfer.h"

double HeatTransfer::area = 0;

double HeatTransfer::convectionCoeficient = 0;

HeatTransfer::HeatTransfer()
{

}

void HeatTransfer::calcArea(double deadVolumeValue, double cylBoreValue, double supDeadPoint, double mechanismPosition, double cylArea)
{
	Constants cte;

	area = 2*cylArea + (4*deadVolumeValue)/cylBoreValue + cte.Pi*cylBoreValue*(supDeadPoint - mechanismPosition);
}

void HeatTransfer::calcConvectionCoef(double NusseltValue, double thermalConductValue, double cylBoreValue)
{
	convectionCoeficient = (NusseltValue*thermalConductValue)/cylBoreValue;
}

double HeatTransfer::getArea()
{
	return area;
}

double HeatTransfer::getConvectionCoef()
{
	return convectionCoeficient;
}