#ifndef AXIS_H
#define AXIS_H

#include "Input.h"
#include "Constants.h"

class Axis
{	
public:
	Axis();

	void calcVelocity();
	
	void setReversibility( double reversibilityValue);
	void setFrequency(double rotationValue);
	
	double getReversibility();
	double getFrequency();
	double getVelocity();
															
protected:
	double reversibility;
	double frequency;
	double velocity;
};

#endif