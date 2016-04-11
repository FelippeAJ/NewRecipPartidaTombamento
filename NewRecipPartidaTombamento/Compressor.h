#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <stdio.h>
#include <time.h>
#include <algorithm>
#include "Constants.h"
#include "SimulationParameters.h"
#include "Input.h"
#include "Refrigerant.h"
#include "Axis.h"
#include "Crank.h"
#include "Rod.h"
#include "Mechanism.h"
#include "Orifice.h"
#include "OrificeFactory.h"
#include "OrificesSet.h"
#include "EffectiveForceArea.h"
#include "DynamicSystem.h"
#include "DynamicSystemFactory.h"
#include "AdimensionalNumbers.h"
#include "HeatTransfer.h"
#include "Cylinder.h"
#include "Piston.h"
#include "Leak.h"
#include "ExperimentalTemperatures.h"
#include "Bearings.h"
#include "Motor.h"
#include "SuctionLine.h"
#include "SuctionMuffler.h"
#include "InternalEnvironment.h"
#include "SuctionChamber.h"
#include "CompressionChamber.h"
#include "MultipleOrifices.h"
#include "DischargeChamber.h"
#include "DischargeMuffler.h"
#include "Bundy.h"
#include "DischargeLine.h"
#include "Evaporator.h"
#include "ExternalEnvironment.h"
#include "Work.h"
#include "PostProcessing.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"
#include "POLOIO.h"
#include "Constants.h"
#include <math.h>

#include <iostream>


using namespace std;

class Compressor 
{
public:
	Compressor();
	void calcPropertiesOfComponents();
	void calcPropertiesOfMechanism();
	void calcSimulationParameters();
	void calcWork();
	void calcEnthalpyFluxInCompressionChamber();
	void exportResults(ofstream &exportData);
	void executePostProcessing(ofstream &outputData);
	void calcEnthalpyFluxOfComponents();
	void calcInputOutputEnergyRateSumOfComponents();
	void simulateCompressor();

	Refrigerant refrigerant;
	SimulationParameters simulParameters;
	Mechanism mechanism;
	CompressionChamber compressionChamberObj;
	MultipleOrifices multiploOrificesObj;
	ExperimentalTemperatures expTemp;
	SuctionLine sucLine;
	SuctionMuffler sucMuffler;
	SuctionChamber sucChamber;
	DischargeChamber disChamber;
	DischargeMuffler disMuffler;
	Bundy bundy;
	DischargeLine disLine;
	InternalEnvironment internalEnvironment;
	Evaporator evaporator;
	ExternalEnvironment externalEnvironment;
	Bearings bearings;
	Motor motor;
	Work work;
	PostProcessing postProcessing;
	Constants cte;

	int contador;	

	int multiplo;



protected:
	int iterative;	
	double n;
	int plotContador;

private:

	
	


};

#endif;

