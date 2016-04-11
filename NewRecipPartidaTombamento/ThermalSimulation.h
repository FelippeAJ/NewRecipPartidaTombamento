#ifndef THERMALSIMULATION_H
#define THERMALSIMULATION_H

#include <iostream>
#include <vector>
#include "Compressor.h"
#include "Jacobian.h"
#include "ThermalBalance.h"
#include "NewtonRaphson.h"
#include "Input.h"
#include "POLOIO.h"

using namespace std;

class ThermalSimulation
{
public:
	ThermalSimulation();


	void setNewTemperatures();
	void setOldTemperature();
	void dimensionVectors();

	void executeThermalSimulation();
	void calcResiduo();
	void calcResiduoPertubaded();

	vector<double> newTemperatures;
	vector<double> oldTemperatures;
	vector<double> temperaturesPertubaded;
	vector<double> residuo;
	vector<vector<double>> residuoPertubaded;

	Compressor compressorObj;

	Jacobian jacobianObj;
	NewtonRaphson newtonRaphsonObj;

	double TLRNCE;
	double RELAX;
	int RESID;
	int CONVER;
	double stopCriteria;

protected:


};

#endif