#ifndef ORIFICE_H
#define ORIFICE_H

#include <cmath>
#include "Input.h"
#include "EffectiveFlowArea.h"


class Orifice
{
public:
	Orifice();

	void calcMassFlow(double gasConst, double specificHeatsRatioMedia, double upstreamTemp, double pressRatio, double  upstreamPress);
	void calcFlow();
	void calcMassSum(double timeStep);
	void calcEnergySum(double timeStep, double enthalpy);
	void calcSuperheatingMassLoses(double suctionChamberRho, double cylinderRho, double timeStep);

	void setDirection(string directionName);
	void setMassFlow(double massFlowValue);

	string getDirection();	
	double getMassFlow();
	double getFlux();
	double getBackFlow();
	double getMassSumFlux();
	double getMassSumBackflow();

	void incrementId();
	static int id;

	EffectiveFlowArea effectFlowAreaObj;

protected:
	string direction;
	double massFlow;	
	double flux;
	double backflow;

	double massSumFlux;
	double energySumFlux;
	double massSumBackflow;
	double energySumBackflow;
	double superheatingMassLoses;
};

#endif