#include "Bearings.h"

Bearings::Bearings()
{
	POLOIO POLOIOobj("input.dat");

	expTemp				=	POLOIOobj.getParamVal("bearings", "left") +273.15;
	los					  =	POLOIOobj.getParamVal("loss", "left");
	avaliationTemperature = POLOIOobj.getParamVal("avaliation_temperature", "left");

}


void Bearings::calcBearingsLos(double motorExpTemp)
{	
	double engineViscosity;

	oilObj.calcViscosity(motorExpTemp);

	engineViscosity = oilObj.getViscosity();

	double bearingViscosity;

	oilObj.calcViscosity(avaliationTemperature);

	bearingViscosity = oilObj.getViscosity();

	bearingsLos = los*engineViscosity/bearingViscosity;
}

double Bearings::getLos()
{
	return los;
}

double Bearings::getAvaliationTemperature()
{
	return avaliationTemperature;
}

double Bearings::getBearingsLos()
{
	return bearingsLos;
}