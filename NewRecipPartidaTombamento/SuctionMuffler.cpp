#include "SuctionMuffler.h"

SuctionMuffler::SuctionMuffler()
{

}
void SuctionMuffler::calcProperties(double sucMufflerTemp, double sucMufflerPressure)
{
	refrigerant.setTemperature(sucMufflerTemp);
	refrigerant.setPressure(sucMufflerPressure);
	refrigerant.calcRho();
	refrigerant.calcEntalphy();
}
void SuctionMuffler::calcEnthalpyFluxToInternalEnvironment(double leakMassSumBackflow, double frequency)
{
	enthalpyFluxToInternalEnvironment = refrigerant.getEnthalpy()*leakMassSumBackflow*frequency ;
}
double SuctionMuffler::getEnthalpyFluxToInternalEnvironment()
{
	return enthalpyFluxToInternalEnvironment;
}
void SuctionMuffler::calcSuctionMufflerAverageTemp(double suctionLineTemp, double suctionChamberTemp)
{
	suctionMufflerAverageTemp = 0.5*(suctionLineTemp + suctionChamberTemp);
}
double SuctionMuffler::getSuctionMufflerAverageTemp()
{
	return suctionMufflerAverageTemp;
}