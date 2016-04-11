#include "Oil.h"

Oil::Oil()
{
	POLOIO POLOIOobj("input.dat");

	expTemp				=	POLOIOobj.getParamVal("oil", "left") + 273.15;
	viscosityCoef1		=	POLOIOobj.getParamVal("viscosisity_coef_1", "left");
	viscosityCoef2		=	POLOIOobj.getParamVal("viscosisity_coef_2", "left");
	viscosityCoef3		=	POLOIOobj.getParamVal("viscosisity_coef_3", "left");

}

void Oil::calcViscosity(double temperatureValue)
{
	viscosity = exp((viscosityCoef1 + viscosityCoef3*temperatureValue)/(1 + viscosityCoef2*temperatureValue) );	
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

