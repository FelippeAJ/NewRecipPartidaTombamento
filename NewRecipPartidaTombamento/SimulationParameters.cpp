#include "SimulationParameters.h"

double SimulationParameters::timeStep = 0;

SimulationParameters::SimulationParameters()
{
	Input simulParamReaderData;

	simulParamReaderData.readSimulationParametersData();

	setDeltaTheta(simulParamReaderData.getSimulParamDeltaTheta());

	setCyclesNumber(simulParamReaderData.getSimulParamCyclesNumber());

	setThermalBalance(simulParamReaderData.getSimulParamThermalBalanceFlag());

	setThermalSimulation(simulParamReaderData.getSimulParamThermalSimulationFlag());

	setDirectSuctionFactor(simulParamReaderData.getSimulParamDirectSuctionFactor());

}

void SimulationParameters::calcFinalTheta()
{
	finalTheta = 2*cte.Pi*cyclesNumber;
}

void SimulationParameters::calcTimeStep(double axisVelocityValue)
{
	timeStep = deltaTheta/axisVelocityValue;	
}

void SimulationParameters::calcLastTheta()
{
	lastTheta = finalTheta - 2*cte.Pi;
}

void SimulationParameters::setDeltaTheta(double deltaThetaValue)
{
	deltaTheta = deltaThetaValue;
}

void SimulationParameters::setDirectSuctionFactor(double directSuctionFactorValue)
{
	directSuctionFactor = directSuctionFactorValue;
}

void SimulationParameters::setCyclesNumber(double cyclesNumberValue)
{
	cyclesNumber = cyclesNumberValue;
}

void SimulationParameters::setThermalBalance(double thermalBalanceFlagValue)
{
	thermalBalanceFlag = thermalBalanceFlagValue;
}
void SimulationParameters::setThermalSimulation(double thermalSimulationFlagValue)
{
	thermalSimulationFlag = thermalSimulationFlagValue;
}

double SimulationParameters::getDeltaTheta()
{
	return deltaTheta;
}

double SimulationParameters::getCyclesNumber()
{
	return cyclesNumber;
}

double SimulationParameters::getFinalTheta()
{
	return finalTheta;
}

double SimulationParameters::getTimeStep()
{
	return timeStep;
}

double SimulationParameters::getLastTheta()
{
	return lastTheta;
}

double SimulationParameters::getThermalBalanceFlag()
{
	return thermalBalanceFlag;
}

double SimulationParameters::getThermalSimulationFlag()
{
	return thermalSimulationFlag;
}

double SimulationParameters::getDirectSuctionFactor()
{
	return directSuctionFactor;
}