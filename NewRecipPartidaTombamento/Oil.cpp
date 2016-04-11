#include "Oil.h"

Oil::Oil()
{
	Input oilReaderData;

	oilReaderData.readOilData();
	
	setViscosityCoef1(oilReaderData.getOilViscosityCoef1());

	setViscosityCoef2(oilReaderData.getOilViscosityCoef2());

	setViscosityCoef3(oilReaderData.getOilViscosityCoef3());
}

void Oil::calcViscosity(double temperatureValue)
{
	viscosity = exp((viscosityCoef1 + viscosityCoef3*temperatureValue)/(1 + viscosityCoef2*temperatureValue) );	
}

void Oil::setViscosityCoef1(double viscosityCoef1Value)
{
	viscosityCoef1 = viscosityCoef1Value;
}

void Oil::setViscosityCoef2(double viscosityCoef2Value)
{
	viscosityCoef2 = viscosityCoef2Value;
}

void Oil::setViscosityCoef3(double viscosityCoef3Value)
{
	viscosityCoef3 = viscosityCoef3Value;
}

double Oil::getViscosityCoef1()
{
	return viscosityCoef1;
}

double Oil::getViscosityCoef2()
{
	return viscosityCoef2;
}

double Oil::getViscosityCoef3()
{
	return viscosityCoef3;
}

double Oil::getViscosity()
{
	return  viscosity;
}

