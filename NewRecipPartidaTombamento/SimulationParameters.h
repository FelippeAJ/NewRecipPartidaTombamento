#ifndef SIMULATIONPARAMETERS_H
#define SIMULATIONPARAMETERS_H

#include "POLOIO.h"
#include "Constants.h"

class SimulationParameters
{
public:
	SimulationParameters();

	void calcFinTheta();
	void calcTimeStep(double shaftVelValue);
	void calcLastTheta();
		
	double getDeltaTheta();
	double getCyclesNum();
	double getFinTheta();
	double getTimeStep();
	double getLastTheta();
	double getThermBalFlag();
	double getThermSimulFlag();
	double getDirectSucFact();

	Constants cte;

protected:
	double deltaTheta;
	static double timeStep;
	double cyclesNum;	
	double lastTheta;
	double finTheta;
	double thermBalFlag;
	double thermSimulFlag;
	double directSucFact;
};

#endif