#include "DischargeLine.h"

DischargeLine::DischargeLine()
{

}

void DischargeLine::calcProperties(double condesationTemp, double disLineTemp)
{
	refrigerant.setTemperature(condesationTemp);

	refrigerant.calcSaturationProperties(1);

	refrigerant.setTemperature(disLineTemp);

	refrigerant.calcRho();

	refrigerant.calcEntalphy();
}

void DischargeLine::calcEnthalpyFluxToOutlet(double massFlowDischarged)
{
	enthalpyFluxToOutlet = massFlowDischarged*refrigerant.getEnthalpy();
}

double DischargeLine::getEnthalpyFluxToOutlet()
{
	return enthalpyFluxToOutlet;
}