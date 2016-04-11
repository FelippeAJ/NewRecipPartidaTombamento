#include "Evaporator.h"

Evaporator::Evaporator()
{
	
}

void Evaporator::calcEnthlapyDiference(double subcoolingTemp, double superHeatingTemp, double evaporationTemp)
{
	double liquidEntalphy;

	double vaporEntalphy;

	refrigerant.setTemperature(subcoolingTemp);

	refrigerant.calcSaturationProperties(1);

	refrigerant.setRho(refrigerant.getRhoLiquid());

	refrigerant.calcEntalphy();

	liquidEntalphy = refrigerant.getEnthalpy();

	
	refrigerant.setTemperature(evaporationTemp);

	refrigerant.calcSaturationProperties(2);


	refrigerant.setTemperature(superHeatingTemp);
	
	refrigerant.calcRho();

	refrigerant.calcEntalphy();


	vaporEntalphy = refrigerant.getEnthalpy();


	enthlapyDiference = vaporEntalphy - liquidEntalphy;
}

double Evaporator::getEnthalpyDiference()
{
	return enthlapyDiference;
}