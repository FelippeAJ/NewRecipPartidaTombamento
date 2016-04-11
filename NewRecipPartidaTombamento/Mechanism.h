#ifndef MECHANISM_H
#define MECHANISM_H

#include <cmath>
#include "Constants.h"
#include "Input.h"
#include "Axis.h"
#include "Crank.h"
#include "Rod.h"
#include "Piston.h"
#include "Oil.h"

class Mechanism
{
public:
	Mechanism();

	void calcSuperiorDeadPoint();
	void calcPosition();
	void calcVelocity();
	void calcVelocityMedia();
	void calcGapFrictionFactor(double cylWallTemp, double sucLinePres, double cylBore, double cylPres);
	void calcContactLength();

	void setMechanism(string mechanismName);
	void setStroke(double strokeValue);

	string getMechanism();
	double getSuperiorDeadPoint();
	double getPosition();
	double getVelocity();
	double getVelocityMedia();
	double getStroke();
	double getGapFrictionFactor();

	Axis axis;
	Crank crank;
	Rod rod;
	Piston piston;
	Oil oil;
	Constants cte;

protected:
	string mechanism;
	double superiorDeadPoint;
	double position;
	static double velocity;
	double velocityMedia;
	double stroke;
	double gapFrictionFactor;
	double contactLength;
};

#endif


