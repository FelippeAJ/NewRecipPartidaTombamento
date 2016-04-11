#include "Impeller.h"
#include "Input.h"

Impeller::Impeller()
{
	height = 0;
	preTension = 0;
}

void Impeller::setHeight(double heightValue)
{
	height =  heightValue;
}

void Impeller::setPreTension(double preTensionValue)
{
	preTension = preTensionValue;
}

double Impeller::getHeight()
{
	return height;
}

double Impeller::getPreTension()
{
	return preTension;
}

