#include "Leak.h"

Leak::Leak()
{
	POLOIO POLOIOobj("input.dat");

	shellPress  =	POLOIOobj.getParamVal("shell_pressure", "left");
	seal		=   POLOIOobj.getWord("seal", "left");

	massFl = 0;
	massSumFl = 0;
	massSumBackf = 0;

	shellPress = -1.0E5;
}

void Leak::calcVel(CompressionChamber compChambObj, double sucLinePress, double visc, double mechVel)
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
		H = compChambObj.getPistHeadLength();
	}
	else
	if(seal == "pin")
	{
		H = compChambObj.getPistHeadLength() + compChambObj.getPistSkirtLength();
	}

	if(shellPress == -1.0E5)
	{
		I = sucLinePress;
	}
	else
	if(shellPress != -1.0E5)
	{
		I = shellPress;
	}

	if(compChambObj.getShape() == "straight")
	{
		A = compChambObj.getPistDiam()/compChambObj.getBore();

		B = (1 - A);

		C = (1 - pow(A,2));

		D = (1 - pow(A,4));

		E = log(A);

		F = (C + 2*pow(A,2)*E)/(2*E*C);

		G = (pow(compChambObj.getPistDiam(),2)/32)*((D/C) + (C/E));

		vel = mechVel*F + (((compChambObj.refrig.getPress() - I)*G)/(H*visc));
	}
	else
	if(compChambObj.getShape() == "conic")
	{
		A1 = compChambObj.getTopDiam()/compChambObj.getBore();

		B1 = (1 - A1);

		C1 = (1 - pow(A1,2));

		D1 = (1 - pow(A1,4));

		E1 = log(A1);

		F1 = (C1 + 2*pow(A1,2)*E1)/(2*E1*C1);

		G1 = (pow(compChambObj.getTopDiam(),2)/32)*((D1/C1) + (C1/E1));

		topVel = mechVel*F1 + (((compChambObj.refrig.getPress() - I)*G1)/(H*visc));

		A2 = compChambObj.getBottDiam()/compChambObj.getBore();

		B2 = (1 - A2);

		C2 = (1 - pow(A2,2));

		D2 = (1 - pow(A2,4));

		E2 = log(A2);

		F2 = (C2 + 2*pow(A2,2)*E2)/(2*E2*C2);

		G2 = (pow(compChambObj.getBottDiam(),2)/32)*((D2/C2) + (C2/E2));

		bottVel = mechVel*F2 + (((compChambObj.refrig.getPress() - I)*G2)/(H*visc));
	}
}

void Leak::calcMassSum(double timeStepValue)
{
	if(massFl > 0)
	{
		massSumFl += massFl*timeStepValue;
	}
	else
	{
		massSumBackf -= massFl*timeStepValue;
	}
}

void Leak::calcMassFl(double oldRhoValue, CompressionChamber compChambObj)
{
	refrig.setTemp(compChambObj.refrig.getTemp());
	refrig.setPress(compChambObj.refrig.getPress());

	refrig.calcRho();

	oldRhoValue = refrig.getRho();

	if(compChambObj.getShape() == "straight")
	{
		massFl = vel*oldRhoValue*compChambObj.getLeakArea();
	}
	else
	if(compChambObj.getShape() == "conic")
	{
		topMassFl = topVel*oldRhoValue*compChambObj.getTopArea();

		bottMassFl = bottVel*oldRhoValue*compChambObj.getBottArea();

		massFl = (topMassFl*bottMassFl)/(topMassFl + bottMassFl);
	}
}

double Leak::getMassFl()
{
	return massFl;
}

double Leak::getMassSumFl()
{
	return massSumFl;
}

double Leak::getMassSumBackf()
{
	return massSumBackf;
}
