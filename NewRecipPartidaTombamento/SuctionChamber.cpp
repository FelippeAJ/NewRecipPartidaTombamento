#include "SuctionChamber.h"

SuctionChamber::SuctionChamber()
{

}

void SuctionChamber::calcProperties(double evaporationTemp, double sucChamberTemp)
{
	refrigerant.setTemperature(evaporationTemp);

	refrigerant.calcSaturationProperties(2);

	refrigerant.setTemperature(sucChamberTemp);

	refrigerant.calcRho();

	refrigerant.calcSpecificHeats();

	refrigerant.calcEntalphy();
}

double SuctionChamber::getEnthalpyFluxToCylinder()
{
	return enthalpyFluxToCylinder;
}

void SuctionChamber::calcEnthalpyFluxToCylinder(double massSumFlux, double frequency)
{
	enthalpyFluxToCylinder = massSumFlux*refrigerant.getEnthalpy()*frequency;
}