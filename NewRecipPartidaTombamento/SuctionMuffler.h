#ifndef SUCTIONMUFFLER_H
#define SUCTIONMUFFLER_H

#include "Input.h"
#include "Refrigerant.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

class SuctionMuffler
{
public:
	SuctionMuffler();

	void calcProperties(double sucMufflerTemp, double sucMufflerPressure);
	void calcEnthalpyFluxToInternalEnvironment(double leakMassSumBackflow, double frequency);
	void calcSuctionMufflerAverageTemp(double suctionLineTemp, double suctionChamberTemp);
	
	double getEnthalpyFluxToInternalEnvironment();
	double getSuctionMufflerAverageTemp();

	Refrigerant refrigerant;
	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;

protected:
	double enthalpyFluxToInternalEnvironment;
	double suctionMufflerAverageTemp;
};

#endif