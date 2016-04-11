#include "Crank.h"

double Crank::theta = 0;

Crank::Crank()
{

}

void Crank::incrementTheta(double deltaThetaValue)
{
	theta += deltaThetaValue;
}

void Crank::setEccentricity(double eccentricityValue)
{
	eccentricity = eccentricityValue;
}

double Crank::getTheta()
{
	return theta;
}

double Crank::getEccentricity()
{
	return eccentricity;
}


