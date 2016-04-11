#include "Piston.h"

double Piston::diameter = 0;

double Piston::distCylBottomPistonPin = 0;

Piston::Piston()
{
	Input pistonReader;

	pistonReader.readCompressionSystemData();

	setHeadLength(pistonReader.getPistonHeadLength());

	setSkirtLength(pistonReader.getPistonSkirtLength());
}

void Piston::calcDiameter(double cylinderBore, double leakGap)
{
	diameter = cylinderBore - leakGap;
}

void Piston::calcDistCylBottomPistonTop(double mechanimPosition, double distCylAxis)
{
	distCylBottomPistonTop = mechanimPosition + headLength - distCylAxis;

	if(distCylBottomPistonTop > (headLength + skirtLength))
	{
		distCylBottomPistonTop = headLength + skirtLength;
	}
}

void Piston::calcDistCylBottomPistonPin()
{
	distCylBottomPistonPin = distCylBottomPistonTop - headLength;
}

void Piston::setHeadLength(double headLengthValue)
{
	headLength = headLengthValue;
}

void Piston::setSkirtLength(double skirtLengthValue)
{
	skirtLength = skirtLengthValue;
}

double Piston::getHeadLength()
{
	return headLength;
}

double Piston::getSkirtLength()
{
	return skirtLength;
}

double Piston::getDistCylBottomPistonPin()
{
	return distCylBottomPistonPin;
}

double Piston::getDiameter()
{
	return diameter;
}

