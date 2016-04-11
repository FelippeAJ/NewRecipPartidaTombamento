#ifndef MULTIPLEORIFICES_H
#define MULTIPLEORIFICES_H

#include <iostream>
#include "OrificeFactory.h"
#include "OrificesSet.h"
#include "DynamicSystemFactory.h"

#include "SuctionChamber.h"
#include "DischargeChamber.h"
#include "Input.h"
#include "Refrigerant.h"

using namespace std;

class MultipleOrifices
{
public:
	MultipleOrifices();

	void creatMultipleOrifices();
	void calcInicialProperties(double sucChamberSpecificHeatsRatio, double disChamberSpecificHeatsRatio);
	void calcValveDynamic(double compressionChamberPressure, SuctionChamber sucChamberObj, DischargeChamber disChamberObj, int stickingForceIndice);
	void calcMassFlow(double compressionChamberPressure, double compressionChamberTemperature, SuctionChamber sucChamberObj, DischargeChamber disChamberObj);

	int getNumberOfOrifices();
	
	void setNumberOfOrifices(int numberOfOrificesValue);

	OrificeFactory orificeFact;
	OrificesSet orificesSet;
	DynamicSystemFactory dynSystemFact;
	Refrigerant refrigerant;

	int stickingForceIndice;

protected:
	int numberOfOrifices;
};

#endif