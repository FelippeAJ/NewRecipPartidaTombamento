#ifndef COMPRESSIONCHAMBER_H
#define COMPRESSIONCHAMBER_H

#include <iostream>
#include <string>
#include "Mechanism.h"
#include "MultipleOrifices.h"
#include "AdimensionalNumbers.h"
#include "HeatTransfer.h"
#include "Cylinder.h"
#include "Piston.h"
#include "Leak.h"
#include "ExperimentalTemperatures.h"

using namespace std;

class CompressionChamber
{
public:
	CompressionChamber();

	void calcInicialProperties(Mechanism mechanism, double sucChamberPressure); 
	void calcTemperature(Mechanism mechanismObj, double sucChamberEnthalpy, double disChamberEnthalpy, MultipleOrifices multiploOrificesObj, double timeStep);
	void calcLeak(double mechanismPosition, double sucLinePressure);
	

	AdimensionalNumbers admNumbers;
	HeatTransfer heatTransf;
	Cylinder cyl;
	Piston piston;
	Leak leak;
	ExperimentalTemperatures experimentalTemperatures;



protected:



};

#endif;