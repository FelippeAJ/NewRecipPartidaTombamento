#ifndef LEAK_H
#define LEAK_H

#include "Input.h"
#include "Constants.h"
#include "Piston.h"
#include "Cylinder.h"
#include "Mechanism.h"
#include "Refrigerant.h"

class Leak
{
public:
	Leak();

	void calcArea();
	void calcGapPistonTop();
	void calcGapPistonPin();
	void calcGapPistonBottom();
	void calcTopDiameter();
	void calcBottomDiameter();
	void calcVelocity(double cylPres, double sucLinePres, double viscosity);
	void calcMassFlow(double oldRho);
	void calcMassSum(double timeStep);

	void setSeal(string sealName);
	void setShellPressure(double shellPressureValue);
	void setGap(double gapValue);
	void setInfDeadPointGap(double gapInfDeadPointValue);

	double getGap();
	double getGapPistonTop();
	double getGapPistonPin();
	double getGapPistonBottom();
	double getVelocity();
	double getMassFlow();
	double getMassSumFlux();
	double getMassSumBackFlow();
	
	Piston piston;
	Cylinder cyl;
	Refrigerant refrigerant;
	Mechanism mec;
	Constants cte;

protected:
	double gap;
	double gapInferiorDeadPoint;
	double gapPistonTop;
	double gapPistonPin;
	double gapPistonBottom;
	double topDiameter;
	double bottomDiameter;
	double area;
	double topArea;
	double bottonArea;
	double shellPressure;
	string seal;
	double velocity;
	double topVelocity;
	double bottomVelocity;
	double massFlow;
	double topMassFlow;
	double bottomMassFlow;
	double massSumFlux;
	double massSumBackFlow;
};

#endif











