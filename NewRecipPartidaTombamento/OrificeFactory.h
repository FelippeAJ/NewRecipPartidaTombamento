#ifndef ORIFICEFACTORY_H
#define ORIFICEFACTORY_H

#include "Input.h"
#include "Orifice.h"

class OrificeFactory
{
public:
	OrificeFactory();

	void creatOrifice();

	Orifice *orifice;

protected:
	Input readOrificeNumber;
};

#endif