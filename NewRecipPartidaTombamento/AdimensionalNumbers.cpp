#include "AdimensionalNumbers.h"

double AdimensionalNumbers::Reynolds = 0;

double AdimensionalNumbers::Prandt = 0;

double AdimensionalNumbers::Nusselt = 0;

AdimensionalNumbers::AdimensionalNumbers()
{

}

void AdimensionalNumbers::calcReynolds(double rhoValue, double velValue, double caractLengthValue, double viscosValue)
{
	Reynolds = (rhoValue*velValue*caractLengthValue)/viscosValue;
}

void AdimensionalNumbers::calcPrandt(double viscosValue,double cpValue, double thermalConductValue)
{
	Prandt = (viscosValue*cpValue)/thermalConductValue;
}

void AdimensionalNumbers::calcNusselt()
{
	Nusselt = 0.7*pow(Reynolds*Prandt,0.7);
}

double AdimensionalNumbers::getReynolds()
{
	return Reynolds;
}

double AdimensionalNumbers::getPrandt()
{
	return Prandt;
}

double AdimensionalNumbers::getNusselt()
{
	return Nusselt;
}