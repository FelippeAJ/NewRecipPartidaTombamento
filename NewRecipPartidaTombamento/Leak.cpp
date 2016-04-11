#include "Leak.h"

Leak::Leak()
{
	Input leakReader;

	leakReader.readLeakData();

	setGap(leakReader.getLeakGap());
	setInfDeadPointGap(leakReader.getLeakInfDeadPointGap());
	setSeal(leakReader.getLeakSeal());
	setShellPressure(leakReader.getLeakShellPressure());

	massFlow = 0;
	massSumFlux = 0;
	massSumBackFlow = 0;
}

void Leak::calcGapPistonTop()
{
	if((mec.getSuperiorDeadPoint() - mec.getPosition()) > (cyl.getLength() - cyl.getConicLength()))
	{
		gapPistonTop = gap + ((mec.getSuperiorDeadPoint() - mec.getPosition()) - (cyl.getLength() - cyl.getConicLength()))*(gapInferiorDeadPoint - gap)/cyl.getConicLength();
	}
	else
	{
		gapPistonTop = gap;
	}
}

void Leak::calcGapPistonPin()
{
	if((mec.getSuperiorDeadPoint() - mec.getPosition() + piston.getHeadLength()) > (cyl.getLength() - cyl.getConicLength()))
	{
		gapPistonPin = gap + ((mec.getSuperiorDeadPoint() - mec.getPosition() + piston.getHeadLength()) - (cyl.getLength() - cyl.getConicLength()))*(gapInferiorDeadPoint - gap)/cyl.getConicLength();
	}
	else
	{
		gapPistonPin = gap;
	}
}

void Leak::calcGapPistonBottom()
{
	if((mec.getSuperiorDeadPoint() - mec.getPosition() + piston.getHeadLength() + piston.getDistCylBottomPistonPin()) > (cyl.getLength() - cyl.getConicLength()))
	{
		gapPistonBottom = gap + ((mec.getSuperiorDeadPoint() - mec.getPosition() + piston.getHeadLength() + piston.getDistCylBottomPistonPin()) - (cyl.getLength() - cyl.getConicLength()))*(gapInferiorDeadPoint - gap)/cyl.getConicLength();
	}
	else
	{
		gapPistonBottom = gap;
	}
}

void Leak::calcVelocity(double cylPres, double sucLinePres, double viscosity)
{
	double A, A1, A2;
	double B, B1, B2;
	double C, C1, C2;
	double D, D1, D2;
	double E, E1, E2;
	double F, F1, F2;
	double G, G1, G2;
	double H;
	double I;

	if(seal == "absent")
	{
		H = piston.getHeadLength();
	}
	else
	if(seal == "pin")
	{
		H = piston.getHeadLength() + piston.getSkirtLength();
	}

	if(shellPressure == -1.0E5)
	{
		I = sucLinePres;
	}
	else
	if(shellPressure != -1.0E5)
	{
		I = shellPressure;
	}

	if(cyl.getCylinder() == "straight")
	{
		A = piston.getDiameter()/cyl.getBore();

		B = (1 - A);

		C = (1 - pow(A,2));

		D = (1 - pow(A,4));

		E = log(A);

		F = (C + 2*pow(A,2)*E)/(2*E*C);

		G = (pow(piston.getDiameter(),2)/32)*((D/C) + (C/E));

		velocity = mec.getVelocity()*F + (((cylPres - I)*G)/(H*viscosity));
	}
	else
	if(cyl.getCylinder() == "conic")
	{
		A1 = topDiameter/cyl.getBore();

		B1 = (1 - A1);

		C1 = (1 - pow(A1,2));

		D1 = (1 - pow(A1,4));

		E1 = log(A1);

		F1 = (C1 + 2*pow(A1,2)*E1)/(2*E1*C1);

		G1 = (pow(topDiameter,2)/32)*((D1/C1) + (C1/E1));

		topVelocity = mec.getVelocity()*F1 + (((cylPres - I)*G1)/(H*viscosity));

		A2 = bottomDiameter/cyl.getBore();

		B2 = (1 - A2);

		C2 = (1 - pow(A2,2));

		D2 = (1 - pow(A2,4));

		E2 = log(A2);

		F2 = (C2 + 2*pow(A2,2)*E2)/(2*E2*C2);

		G2 = (pow(bottomDiameter,2)/32)*((D2/C2) + (C2/E2));

		bottomVelocity = mec.getVelocity()*F2 + (((cylPres - I)*G2)/(H*viscosity));
	}
}

void Leak::calcMassSum(double timeStepValue)
{
	if(massFlow > 0)
	{
		massSumFlux += massFlow*timeStepValue;
	}
	else
	{
		massSumBackFlow -= massFlow*timeStepValue;
	}
}

void Leak::calcTopDiameter()
{
	topDiameter = cyl.getBore() - (gapPistonTop + gapPistonPin)/2;
}

void Leak::calcBottomDiameter()
{
	bottomDiameter = cyl.getBore() - (gapPistonPin + gapPistonPin)/2;
}


void Leak::calcArea()
{
	if(cyl.getCylinder() == "straight")
	{
		area = cyl.getArea() - (cte.Pi*pow(piston.getDiameter(),2))/4;
	}
	else
	if(cyl.getCylinder() == "conic")
	{
		topArea = cyl.getArea() - (cte.Pi*pow(topDiameter,2))/4;

		bottonArea = cyl.getArea() - (cte.Pi*pow(bottomDiameter,2))/4;
	}
}

void Leak::calcMassFlow(double oldRhoValue)
{
	if(cyl.getCylinder() == "straight")
	{
		massFlow = velocity*oldRhoValue*area;
	}
	else
	if(cyl.getCylinder() == "conic")
	{
		topMassFlow = topVelocity*oldRhoValue*topArea;

		bottomMassFlow = bottomVelocity*oldRhoValue*bottonArea;

		massFlow = (topMassFlow*bottomMassFlow)/(topMassFlow + bottomMassFlow);
	}
}

void Leak::setGap(double gapValue)
{
	gap = gapValue;
}

void Leak::setInfDeadPointGap(double gapInfDeadPointValue)
{
	gapInferiorDeadPoint = gapInfDeadPointValue;
}

void Leak::setSeal(string sealName)
{
	seal= sealName;
}

void Leak::setShellPressure(double shellPressureValue)
{
	shellPressure = shellPressureValue;
}

double Leak::getGap()
{
	return gap;
}

double Leak::getGapPistonTop()
{
	return gapPistonTop;
}

double Leak::getGapPistonPin()
{
	return gapPistonPin;
}

double Leak::getGapPistonBottom()
{
	return gapPistonBottom;
}

double Leak::getVelocity()
{
	return velocity;
}

double Leak::getMassFlow()
{
	return massFlow;
}

double Leak::getMassSumFlux()
{
	return massSumFlux;
}

double Leak::getMassSumBackFlow()
{
	return massSumBackFlow;
}
