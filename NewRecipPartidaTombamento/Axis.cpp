#include "Axis.h"

Axis::Axis()
{

}

void Axis::calcVelocity()
{
	Constants cte;
	velocity = 2*cte.Pi*frequency;
}

void Axis::setReversibility(double reversibilityValue)
{
	reversibility = reversibilityValue;
}

void Axis::setFrequency(double rotationValue)
{
	frequency = rotationValue/60;
}

double Axis::getReversibility()
{
	return reversibility;
}

double Axis::getFrequency()
{
	return frequency;
}

double Axis::getVelocity()
{
	return velocity;
}
