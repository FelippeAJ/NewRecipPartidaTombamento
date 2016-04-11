#include "Valve.h"
#include "Input.h"

Valve::Valve()
{
	preTension = 0;
}

void Valve::calcEquivalentMass()
{
	Constants cte;

	equivalentMass = stiffness/pow((2*cte.Pi*natFrequency),2);
}

void Valve::setNatFrequency(double natFrequencyValue)
{
	natFrequency = natFrequencyValue;
}

void Valve::setStiffness(double stiffnessValue)
{
	stiffness = stiffnessValue;
}

void Valve::setDamping(double dampingValue)
{
	damping = dampingValue;
}

void Valve::setPreTension(double preTensionValue)
{
	preTension = preTensionValue;
}

double Valve::getStiffness()
{
	return stiffness;
}

double Valve::getNatFrequency()
{
	return natFrequency;
}

double Valve::getDamping()
{
	return damping;
}

double Valve::getPreTension()
{
	return preTension;
}

double Valve::getEquivalentMass()
{
	return equivalentMass;
}
