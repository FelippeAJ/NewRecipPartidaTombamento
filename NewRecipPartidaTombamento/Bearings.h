#ifndef BEARINGS_H
#define BEARINGS_H

#include "POLOIO.h"
#include "Oil.h"

class Bearings
{
public:
	Bearings();

	void calcBearingsLos(double motorExpTemp);

	double getLos();
	double getAvaliationTemperature();
	double getBearingsLos();

	Oil oilObj;

	double expTemp;

protected:
	double los;
	double avaliationTemperature;
	double bearingsLos;
	
	
};

#endif