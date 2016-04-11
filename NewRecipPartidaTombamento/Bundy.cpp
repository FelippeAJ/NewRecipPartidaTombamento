#include "Bundy.h"

Bundy::Bundy()
{

}

void Bundy::calcProperties(double condesationTemp, double dischargeMufflerTemp)
{
	refrigerant.setTemperature(condesationTemp);

	refrigerant.calcSaturationProperties(1);

	refrigerant.setTemperature(dischargeMufflerTemp);

	refrigerant.calcRho();

	refrigerant.calcSpecificHeats();

	refrigerant.calcEntalphy();

}

void Bundy::calcEnthalpyFluxToDischargeLine(double massFlowDischarged)
{
	enthalpyFluxToDischargeLine = massFlowDischarged*refrigerant.getEnthalpy();
}
void Bundy::calcBundyAverageTemp(double dischargeMufflerTemp, double dischargeLineTemp)
{
	bundyAverageTemp = 0.50*(dischargeMufflerTemp + dischargeLineTemp);
}

double Bundy::getEnthalpyFluxToDischargeLine()
{
	return enthalpyFluxToDischargeLine;
}
double Bundy::getBundyAverageTemp()
{
	return bundyAverageTemp;
}
