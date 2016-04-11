#include "SimulationParameters.h"

double SimulationParameters::timeStep = 0;

SimulationParameters::SimulationParameters()
{
	POLOIO POLOIOobj("input.dat");

	deltaTheta		=	POLOIOobj.getParamVal("delta_theta", "left");
	cyclesNum		=	POLOIOobj.getParamVal("cycles_number", "left");
	thermBalFlag	=	POLOIOobj.getParamVal("thermal_balance", "left");
	thermSimulFlag	=	POLOIOobj.getParamVal("thermal_simulation", "left");
	directSucFact	=	POLOIOobj.getParamVal("direct_suction_factor", "left");

}

void SimulationParameters::calcFinTheta()
{
	finTheta = 2*cte.Pi*cyclesNum;
}

void SimulationParameters::calcTimeStep(double shaftVelValue)
{
	timeStep = deltaTheta/shaftVelValue;	
}

void SimulationParameters::calcLastTheta()
{
	lastTheta = finTheta - 2*cte.Pi;
}

double SimulationParameters::getDeltaTheta()
{
	return deltaTheta;
}

double SimulationParameters::getCyclesNum()
{
	return cyclesNum;
}

double SimulationParameters::getFinTheta()
{
	return finTheta;
}

double SimulationParameters::getTimeStep()
{
	return timeStep;
}

double SimulationParameters::getLastTheta()
{
	return lastTheta;
}

double SimulationParameters::getThermBalFlag()
{
	return thermBalFlag;
}

double SimulationParameters::getThermSimulFlag()
{
	return thermSimulFlag;
}

double SimulationParameters::getDirectSucFact()
{
	return directSucFact;
}