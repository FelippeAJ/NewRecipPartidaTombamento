#include "Motor.h"

Motor::Motor()
{
	Input engineReaderData;

	engineReaderData.contMotorCoefNumber();

	engineReaderData.dimensionMotorCoef();

	engineReaderData.readMotorData();

	setCoef(engineReaderData.getMotorCoef());

}

void Motor::setCoef(vector<double> coeficientsValue)
{
	for(int i = 0; i < coeficientsValue.size(); i++)
	{
		coeficients.push_back(coeficientsValue[i]);
	}
}

double Motor::getCoeficients(int id)
{
	return coeficients[id];
}

void Motor::calcEfficiency(double axisPotency)
{
	efficiency = interp.polynomialInterp(coeficients.size(), coeficients, axisPotency); 
}

void Motor::calcHeat(double consumption)
{
	heat = (1 - efficiency)*consumption;
}

double Motor::getEfficiency()
{
	return efficiency;
}

double Motor::getHeat()
{
	return heat;
}
