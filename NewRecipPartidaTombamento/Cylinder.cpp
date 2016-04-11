#include "Cylinder.h"
#include "Input.h"

string Cylinder::cylinder = "Cylinder";

double Cylinder::derivateVolume = 0;

double Cylinder::area = 0;
Cylinder::Cylinder()
{
	Input cylinderReader;

	cylinderReader.readCompressionSystemData();

	setCylinder(cylinderReader.getCylinderShape());

	setBore(cylinderReader.getCylinderBore());

	setDeadVolume(cylinderReader.getCylinderDeadVolume());

	setLength(cylinderReader.getCylinderLength());

	setConicLength(cylinderReader.getCylinderConicLength());

	setAxisDistance(cylinderReader.getCylinderAxisDistance());

	enthalpyFluxToSuctionChamber = 0;

	enthalpyFluxToDischargeChamber = 0;

	enthalpyFluxToInternalEnvironment = 0;
}
void Cylinder::calcArea()
{
	Constants cte;

	area = (cte.Pi*pow(bore,2))/4 ;
}
void Cylinder::calcVolume(double supDeadPointValue, double mechanismPositionValue)
{
	volume = deadVolume + area*( supDeadPointValue - mechanismPositionValue);
}
void Cylinder::calcDisplacementVolume(double strokeValue)
{
	displacementVolume = strokeValue*area;
}
void Cylinder::calcDerivateVolume(double mechanismVelocity)
{
	derivateVolume = -area*mechanismVelocity;
}
void Cylinder::calcDerivateTemperature(double sucChamberEnthalpy, double disChamberEnthalpy, double sucOrifFlux, double sucOrifBackFlow, double discOrifFlux, double discOrifBackFlow)
{
	double A = 1/(refrigerant.getMass()*refrigerant.getCv());

	double B = heatTransfer.getConvectionCoef()*heatTransfer.getArea();

	double C = A*(B*(expTemp.getCylinderWallTemp()) + sucOrifFlux*(sucChamberEnthalpy - refrigerant.getEnthalpy()) + discOrifBackFlow*(disChamberEnthalpy - refrigerant.getEnthalpy()));

	double D = A*(B +  refrigerant.getDPresDTemp()*derivateVolume - refrigerant.getDPresDTemp()*(1/refrigerant.getRho())*(sucOrifFlux - discOrifFlux - sucOrifBackFlow + discOrifBackFlow));
	
	derivateTemperature = C - D*refrigerant.getTemperature();
}
void Cylinder::calcMassBalance(double sucOrifFlow, double disOrifFlow, double leakFlow, double timeStepValue)
{
	double massTemp = 0;

	massTemp = refrigerant.getMass() + (sucOrifFlow - disOrifFlow - leakFlow )*timeStepValue;

	refrigerant.setMass(massTemp);
}
void Cylinder::calcEnthalpyFluxToDischargeChamber(double flux, double timeStep)
{
	enthalpyFluxToDischargeChamber += flux*refrigerant.getEnthalpy()*timeStep;
}
void Cylinder::calcEnthalpyFluxToSuctionChamber(double backflow, double timeStep)
{
	enthalpyFluxToSuctionChamber += backflow*refrigerant.getEnthalpy()*timeStep;
}
void Cylinder::calcEnthalpyFluxToInternalEnvironment(double leakFlux, double timeStep)
{
	if(leakFlux > 0)
	{
		enthalpyFluxToInternalEnvironment += leakFlux*refrigerant.getEnthalpy()*timeStep;
	}
	else
	{
		leakFlux = 0;
		enthalpyFluxToInternalEnvironment += leakFlux*refrigerant.getEnthalpy()*timeStep;
	}
}
void Cylinder::calcEnthalpyFluxToDischargeChamberAverage(double enthalpyFluxToDischargeChamber, double frequency)
{
	enthalpyFluxToDischargeChamberAverage = enthalpyFluxToDischargeChamber*frequency;
}
void Cylinder::calcEnthalpyFluxToSuctionChamberAverage(double enthalpyFluxToSuctionChamber, double frequency)
{
	enthalpyFluxToSuctionChamberAverage = enthalpyFluxToSuctionChamber*frequency;
}
void Cylinder::calcEnthalpyFluxToInternalEnvironmentAverage( double enthalpyFluxToInternalEnvironment, double frequency)
{
	enthalpyFluxToInternalEnvironmentAverage = enthalpyFluxToInternalEnvironment*frequency; 
}
void Cylinder::setCylinder(string cylinderName)
{
	cylinder = cylinderName;
}
void Cylinder::setBore(double boreValue)
{
	bore = boreValue;
}
void Cylinder::setDeadVolume(double deadVolumeValue)
{
	deadVolume = deadVolumeValue;
}
void Cylinder::setLength(double lengthValue)
{
	length = lengthValue;	
}
void Cylinder::setConicLength(double conicLengthValue)
{
	conicLength = conicLengthValue;	
}
void Cylinder::setAxisDistance(double axisDistanceValue)
{
	axisDistance = axisDistanceValue;	
}
string Cylinder::getCylinder()
{
	return cylinder;
}
double Cylinder::getBore()
{
	return bore;
}
double Cylinder::getDeadVolume()
{
	return deadVolume;
}
double Cylinder::getLength()
{
	return length;
}
double Cylinder::getConicLength()
{
	return conicLength;
}
double Cylinder::getAxisDistance()
{
	return axisDistance;
}
double Cylinder::getArea()
{
	return area;
}
double Cylinder::getVolume()
{
	return volume;
}
double Cylinder::getDisplacementVolume()
{
	return displacementVolume;
}
double Cylinder::getDerivateTemperature()
{
	return derivateTemperature;
}
double Cylinder::getEnthalpyFluxToDischargeChamber()
{
	return enthalpyFluxToDischargeChamber;
}
double Cylinder::getEnthalpyFluxToSuctionChamber()
{
	return enthalpyFluxToSuctionChamber;
}
double Cylinder::getEnthalpyFluxToInternalEnvironment()
{
	return enthalpyFluxToInternalEnvironment;
}
double Cylinder::getEnthalpyFluxToDischargeChamberAverage()
{
	return enthalpyFluxToDischargeChamberAverage;
}
double Cylinder::getEnthalpyFluxToSuctionChamberAverage()
{
	return enthalpyFluxToSuctionChamberAverage;
}
double Cylinder::getEnthalpyFluxToInternalEnvironmentAverage()
{
	return enthalpyFluxToInternalEnvironmentAverage;
}
