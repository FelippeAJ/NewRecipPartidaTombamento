#ifndef BEARINGS_H
#define BEARINGS_H

#include "Input.h"
#include "ExperimentalTemperatures.h"
#include "Oil.h"

class Bearings
{
public:
	Bearings();

	void setLoses(double losesValue);
	void setAvaliationTemperature(double avaliationTemperatureValue);

	void calcBearingsLoses();

	double getLoses();
	double getAvaliationTemperature();
	double getBearingsLoses();

protected:
	double loses;
	double avaliationTemperature;
	double bearingsLoses;
	ExperimentalTemperatures expTemperature;
	Oil oil;
};

#endif