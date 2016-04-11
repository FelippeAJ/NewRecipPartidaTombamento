#ifndef PISTON_H
#define PISTON_H

#include <cmath>
#include "Input.h"
#include "Constants.h"

class Piston
{
public:
	Piston();

	void calcDiameter(double cylBore, double leakGap);
	void calcDistCylBottomPistonTop(double mechanimPosition, double distCylAxis);
	void calcDistCylBottomPistonPin();

	void setHeadLength(double headLengthValue);
	void setSkirtLength(double skirtLengthValue);

	double getHeadLength();
	double getSkirtLength();
	double getDistCylBottomPistonPin();
	double getDiameter();
	
	Constants cte;
	
protected:
	double skirtLength;
	double headLength;
	static double diameter;
	double distCylBottomPistonTop;
	static double distCylBottomPistonPin;
};

#endif