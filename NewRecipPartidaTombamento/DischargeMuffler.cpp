#include "DischargeMuffler.h"

DischargeMuffler::DischargeMuffler()
{

}

void DischargeMuffler::calcProperties(double condensingTemp, double dischargeMufflerTemperature)
{
	refrigerant.setTemperature(condensingTemp);

	refrigerant.calcSaturationProperties(2);

	refrigerant.setTemperature(dischargeMufflerTemperature);

	refrigerant.calcRho();

	refrigerant.calcEntalphy();
}

void DischargeMuffler::calcEnthalpyFluxtoBundy(double massFlowDischarged)
{
	enthalpyFluxtoBundy = massFlowDischarged*refrigerant.getEnthalpy();
}
double DischargeMuffler::getEnthalpyFluxtoBundy()
{
	return enthalpyFluxtoBundy;
}
void DischargeMuffler::calcDischargeMufflerAverageTemp(double dischargeChamberTemp, double dischargeMufflerTemp)
{
	dischargeMufflerAverageTemp = 0.50*(dischargeChamberTemp + dischargeMufflerTemp);
}

double DischargeMuffler::getDischargeMufflerAverageTemp()
{
	return dischargeMufflerAverageTemp;
}
