#include "SuctionLine.h"

SuctionLine::SuctionLine()
{

}

void SuctionLine::calcProperties(double evaporationTemp, double sucLineTemp)
{
	refrigerant.setTemperature(evaporationTemp);

	refrigerant.calcSaturationProperties(2);

	refrigerant.setTemperature(sucLineTemp);

	refrigerant.calcRho();

	refrigerant.calcEntalphy();


}

void SuctionLine::calcEnthalpyFluxtoSuctionMuffler(double massFlowDischarged, double directSuctionFactor)
{
	enthalpyFluxtoSuctionMuffler = directSuctionFactor*massFlowDischarged*refrigerant.getEnthalpy();
}

void SuctionLine::calcEnthalpyFluxtoInternalEnvironment(double massFlowDischarged)
{
	enthalpyFluxtoInternalEnvironment = massFlowDischarged*refrigerant.getEnthalpy();
}

double SuctionLine::getEnthalpyFluxtoSuctionMuffler()
{
	return enthalpyFluxtoSuctionMuffler;
}

double SuctionLine::getEnthalpyFluxtoInternalEnvironment()
{
	return enthalpyFluxtoInternalEnvironment;
}