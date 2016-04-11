#include "DischargeChamber.h"

DischargeChamber::DischargeChamber()
{

}

void DischargeChamber::calcProperties(double condesationTemp, double disChamberTemp)
{
	refrigerant.setTemperature(condesationTemp);

	refrigerant.calcSaturationProperties(1);

	refrigerant.setTemperature(disChamberTemp);

	refrigerant.calcRho();

	refrigerant.calcSpecificHeats();

	refrigerant.calcEntalphy();
}

void DischargeChamber::calcEnthalpyFluxToDischargeMuffler(double massFlowDischarged)
{
	enthalpyFluxToDischargeMuffler = massFlowDischarged*refrigerant.getEnthalpy();
}
double DischargeChamber::getEnthalpyFluxToDischargeMuffler()
{
	return enthalpyFluxToDischargeMuffler;
}
void DischargeChamber::calcEnthalpyFluxToCylinder(double massSumBackflow, double frequency)
{
	enthalpyFluxToCylinder = massSumBackflow*refrigerant.getEnthalpy()*frequency;
}
double DischargeChamber::getEnthalpyFluxToCylinder()
{
	return enthalpyFluxToCylinder;
}
