#include "Bearings.h"

Bearings::Bearings()
{
	Input bearingReaderData;

	bearingReaderData.readBearingsData();

	setLoses(bearingReaderData.getBearingsLoses());

	setAvaliationTemperature(bearingReaderData.getBearingsAvaliationTemperature());
}

void Bearings::setLoses(double losesValue)
{
	loses = losesValue;
}

void Bearings::setAvaliationTemperature(double avaliationTemperatureValue)
{
	avaliationTemperature = avaliationTemperatureValue;
}

void Bearings::calcBearingsLoses()
{	
	double engineViscosity;

	oil.calcViscosity(expTemperature.getMotorTemp());

	engineViscosity = oil.getViscosity();

	double bearingViscosity;

	oil.calcViscosity(avaliationTemperature);

	bearingViscosity = oil.getViscosity();

	bearingsLoses = loses*engineViscosity/bearingViscosity;
}

double Bearings::getLoses()
{
	return loses;
}

double Bearings::getAvaliationTemperature()
{
	return avaliationTemperature;
}

double Bearings::getBearingsLoses()
{
	return bearingsLoses;
}