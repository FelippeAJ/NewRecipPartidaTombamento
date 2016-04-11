#include "Mechanism.h"

double Mechanism::velocity = 0;

Mechanism::Mechanism()
{
	Input mechanismReaderData;

	mechanismReaderData.readMechanismData();

	setMechanism(mechanismReaderData.getMechanismDisplacement());

	setStroke(mechanismReaderData.getMechanismStroke());

	axis.setReversibility(mechanismReaderData.getAxisReversibility());

	axis.setFrequency(mechanismReaderData.getAxisRotation());

	crank.setEccentricity(mechanismReaderData.getCrankEccentricity());

	rod.setLength(mechanismReaderData.getRodLength());
}


void Mechanism::calcSuperiorDeadPoint()
{
	if(mechanism == "crank_rod")
	{
		double A = (rod.getLength() + crank.getEccentricity());

		superiorDeadPoint = sqrt(pow(A,2) - pow( axis.getReversibility(),2));
	}
	else
	if(mechanism == "sinusoidal")
	{
		superiorDeadPoint = stroke;
	}
	else
	{
		cout << "Undeclared Mechanism." << endl;
	}
}

void Mechanism::calcPosition()
{
	if(mechanism == "crank_rod")
	{
		double A = crank.getEccentricity()*cos(crank.getTheta());
		double B = crank.getEccentricity()*sin(crank.getTheta());
		double C = pow(rod.getLength(),2) - pow((B - axis.getReversibility()),2);

		position = -A + sqrt(C);
	}
	else
	if(mechanism == "sinusoidal")
	{
		position = (stroke/2)*sin(crank.getTheta()+3*cte.Pi/2) + (stroke/2);
	}
	else
	{
		cout << "Undeclared Mechanism." << endl;
	}
}

void Mechanism::calcVelocity()
{
	if(mechanism == "crank_rod")
	{
		double A = crank.getEccentricity()*cos(crank.getTheta());
		double B = crank.getEccentricity()*sin(crank.getTheta());
		double C = pow(rod.getLength(),2) - pow((B - axis.getReversibility()),2);

		velocity = (B - ((B - axis.getReversibility())*A)/sqrt(C))*axis.getVelocity();
	}
	else
	if(mechanism == "sinusoidal")
	{
		velocity = ((stroke/2)*cos(crank.getTheta()+3*cte.Pi/2))*axis.getVelocity();
	}
	else
	{
		cout << "Undeclared Mechanism." << endl;
	}
}

void Mechanism::calcVelocityMedia()
{	
	if(mechanism == "crank_rod")
	{
		velocityMedia = 4*axis.getFrequency()*crank.getEccentricity();
	}
	else
	if(mechanism == "sinusoidal")
	{
		velocityMedia = 2*axis.getFrequency()*stroke;
	}
	else
	{
		cout << "Undeclared Mechanism." << endl;
	}
}

void Mechanism::calcGapFrictionFactor(double cylWallTemp, double sucLinePres, double cylBore, double cylPres)
{
	double diameterRatio = piston.getDiameter()/cylBore;

	double A = log(diameterRatio);

	double B = pow(diameterRatio, 2);

	oil.calcViscosity(cylWallTemp);

	gapFrictionFactor= -( ( ( 2*cte.Pi*oil.getViscosity()*contactLength) / A)*velocity	+  ((cylPres - sucLinePres)/2.0)*cte.Pi*pow((piston.getDiameter()/2),2)*((2.0 * B * A + 1.0 - B)/A ) );
}

void Mechanism::calcContactLength()
{
	contactLength = piston.getHeadLength() + piston.getSkirtLength();
}

void Mechanism::setMechanism(string mechanismName)
{
	mechanism = mechanismName;
}

void Mechanism::setStroke(double strokeValue)
{
	 stroke = strokeValue;
}

string Mechanism::getMechanism()
{
	return mechanism;
}

double Mechanism::getStroke()
{
	return stroke;
}

double Mechanism::getGapFrictionFactor()
{
	return gapFrictionFactor;
}

double Mechanism::getSuperiorDeadPoint()
{
	return superiorDeadPoint;
}

double Mechanism::getPosition()
{
	return position;
}

double Mechanism::getVelocity()
{
	return velocity;
}

double Mechanism::getVelocityMedia()
{
	return velocityMedia;
}




