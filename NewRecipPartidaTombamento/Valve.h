#ifndef VALVE_H
#define VALVE_H

#include <cmath>
#include "Constants.h"
#include "Input.h"


class Valve
{
public:
	Valve();

	void setNatFrequency( double natFrequencyValue);
	void setStiffness( double stiffnessValue);
	void setDamping( double dampingValue);  
	void setPreTension(double preTensionValue);
	
	double getNatFrequency();
	double getStiffness();
	double getDamping();
	double getPreTension();
	double getEquivalentMass();

	void calcEquivalentMass();

protected:
	double natFrequency;
	double stiffness;
	double damping;
	double preTension;
	double equivalentMass;	
};

#endif