#include "InternalEnvironment.h"
InternalEnvironment::InternalEnvironment()
{


}
void InternalEnvironment::calcProperties(double internalEnvironmentTemp, double sucLinePressure)
{
	refrigerant.setTemperature(internalEnvironmentTemp);
	refrigerant.setPressure(sucLinePressure);
	refrigerant.calcEntalphy();
}
void InternalEnvironment::calcEnthalpyFluxToSuctionMuffler(double leakLoses, double massFlowDischarged, double directSuctionFactor)
{
	enthalpyFluxToSuctionMuffler = leakLoses*refrigerant.getEnthalpy() + massFlowDischarged*(1 - directSuctionFactor)*refrigerant.getEnthalpy();
}
void InternalEnvironment::calcEnthalpyFluxToCylinder(double leakMassSumBackflow, double frequency)
{
	enthalpyFluxToCylinder = refrigerant.getEnthalpy()*leakMassSumBackflow*frequency;
}

double InternalEnvironment::getEnthalpyFluxToSuctionMuffler()
{
	return enthalpyFluxToSuctionMuffler;
}
double InternalEnvironment::getEnthalpyFluxToCylinder()
{
	return enthalpyFluxToCylinder;
}
