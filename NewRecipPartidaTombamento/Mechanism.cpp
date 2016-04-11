#include "Mechanism.h"

double Mechanism::vel = 0;
double Mechanism::theta = 0;

Mechanism::Mechanism()
{
	POLOIO POLOIOobj("input.dat");

	mech		=	POLOIOobj.getWord("mechanism_displacement", "left");
	stroke		=	POLOIOobj.getParamVal("stroke", "left");
	revers		=	POLOIOobj.getParamVal("reversibility", "left");
	rot			=	POLOIOobj.getParamVal("rotation", "left");
	eccent		=	POLOIOobj.getParamVal("eccentricity", "left");
	rodLength	=	POLOIOobj.getParamVal("rod_length", "left");
	
	freq = rot/60;
}

void Mechanism::calcSupDeadPt()
{
	if(mech == "crank_rod")
	{
		supDeadPt = sqrt(pow(rodLength + eccent,2) - pow(revers,2));
	}
	else
	if(mech == "sinusoidal")
	{
		supDeadPt = stroke;
	}
}

void Mechanism::calcPos()
{
	if(mech == "crank_rod")
	{
		double A = eccent*cos(theta);
		double B = eccent*sin(theta);
		double C = pow(rodLength,2) - pow((B - revers),2);

		pos = -A + sqrt(C);
	}
	else
	if(mech == "sinusoidal")
	{
		pos = (stroke/2)*sin(theta+3*cte.Pi/2) + (stroke/2);
	}
}

void Mechanism::calcVel()
{
	if(mech == "crank_rod")
	{
		double A = eccent*cos(theta);
		double B = eccent*sin(theta);
		double C = pow(rodLength,2) - pow(B - revers,2);

		vel = (B - ((B - revers)*A)/sqrt(C))*shaftVel;
	}
	else
	if(mech == "sinusoidal")
	{
		vel = ((stroke/2)*cos(theta + 3*cte.Pi/2))*shaftVel;
	}
}

void Mechanism::calcVelMed()
{	
	if(mech == "crank_rod")
	{
		velMed = 4*freq*eccent;
	}
	else
	if(mech == "sinusoidal")
	{
		velMed = 2*freq*stroke;
	}
}

void Mechanism::calcShaftVel()
{
	Constants cte;
	shaftVel = 2*cte.Pi*freq;
}

void Mechanism::incremTheta(double deltaTheta)
{
	theta += deltaTheta;
}

double Mechanism::getSupDeadPt()
{
	return supDeadPt;
}

double Mechanism::getPos()
{
	return pos;
}

double Mechanism::getVel()
{
	return vel;
}

double Mechanism::getVelMed()
{
	return velMed;
}

double Mechanism::getShaftVel()
{
	return shaftVel;
}

double Mechanism::getFreq()
{
	return freq;
}

double Mechanism::getEccent()
{
	return eccent;
}

double  Mechanism::getTheta()
{
	return theta;
}

double  Mechanism::getStroke()
{
	return stroke;
}

string Mechanism::getMech()
{
	return mech;
}






