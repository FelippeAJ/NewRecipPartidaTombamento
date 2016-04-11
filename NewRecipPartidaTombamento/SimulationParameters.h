#ifndef SIMULATIONPARAMETERS_H
#define SIMULATIONPARAMETERS_H

#include "Input.h"
#include "Constants.h"

class SimulationParameters
{
public:
	SimulationParameters();

	void calcFinalTheta();
	void calcTimeStep(double axisVelocityValue);
	void calcLastTheta();

	void setDeltaTheta(double deltaThetaValue);
	void setCyclesNumber(double cyclesNumberValue);
	void setThermalBalance(double thermalBalanceFlagValue);
	void setThermalSimulation(double thermalSimulationFlagValue);
	void setDirectSuctionFactor (double directSuctionFactorValue);
		
	double getDeltaTheta();
	double getCyclesNumber();
	double getFinalTheta();
	double getTimeStep();
	double getLastTheta();
	double getThermalBalanceFlag();
	double getThermalSimulationFlag();
	double getDirectSuctionFactor();
	
	Constants cte;

protected:
	double deltaTheta;
	static double timeStep;
	double cyclesNumber;	
	double lastTheta;
	double finalTheta;
	double thermalBalanceFlag;
	double thermalSimulationFlag;
	double directSuctionFactor;
};

#endif