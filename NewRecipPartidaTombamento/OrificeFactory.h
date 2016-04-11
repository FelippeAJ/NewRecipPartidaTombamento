#ifndef ORIFICEFACTORY_H
#define ORIFICEFACTORY_H

#include "POLOIO.h"
#include "Orifice.h"

class OrificeFactory
{
public:
	OrificeFactory();

	void creatOrifice();
	double getOrifNum();

	Orifice *orifice;

protected:
	int orifNum;
};

#endif