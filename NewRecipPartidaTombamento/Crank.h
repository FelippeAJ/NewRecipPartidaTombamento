#ifndef CRANK_H
#define CRANK_H

#include "Input.h"
#include "Constants.h"

class Crank
{
public:
	Crank();

	void setEccentricity(double eccentricityValue);
	
	double getEccentricity();
	double getTheta();

	void incrementTheta(double deltaThetaValue);

	static double theta;

protected:
	double eccentricity;
	
};

#endif
