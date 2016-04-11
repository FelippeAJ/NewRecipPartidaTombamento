#ifndef CYLINDER_H
#define CYLINDER_H

#include <cmath>
#include "Input.h"
#include "Constants.h"
#include "Refrigerant.h"
#include "ExperimentalTemperatures.h"
#include "HeatTransfer.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

class Cylinder
{
public:
	Cylinder();

	void calcArea();
	void calcVolume(double supDeadPointValue, double mechanismPositionValue);
	void calcDisplacementVolume(double stroke);
	void calcDerivateVolume(double mechanismVelocity);
	void calcDerivateTemperature(double sucChamberEnthalpy, double disChamberEnthalpy, double sucOrifFlux, double sucOrifBackFlow, double discOrifFlux, double discOrifBackFlow);
	void calcMassBalance(double sucOrifFlow, double disOrifFlow, double leakFlow, double timeStepValue);

	void setCylinder(string cylinderName);
	void setBore(double boreValue);
	void setDeadVolume(double deadVolumeValue);
	void setLength(double lengthValue);
	void setConicLength(double conicLengthValue);
	void setAxisDistance(double axisDistanceValue);

	void calcEnthalpyFluxToDischargeChamber(double flux, double timeStep);
	void calcEnthalpyFluxToSuctionChamber(double backflow, double timeStep);
	void calcEnthalpyFluxToInternalEnvironment(double leakFlux, double timeStep);
	void calcEnthalpyFluxToDischargeChamberAverage(double enthalpyFluxToDischargeChamber, double frequency);
	void calcEnthalpyFluxToSuctionChamberAverage(double enthalpyFluxToSuctionChamber, double frequency);
	void calcEnthalpyFluxToInternalEnvironmentAverage(double enthalpyFluxToInternalEnvironment, double frequency);

	string getCylinder();
	double getBore();
	double getDeadVolume();
	double getLength();
	double getConicLength();
	double getAxisDistance();
	double getArea();
	double getVolume();
	double getDisplacementVolume();
	double getDerivateTemperature();
	double getEnthalpyFluxToDischargeChamber();
	double getEnthalpyFluxToSuctionChamber();
	double getEnthalpyFluxToInternalEnvironment();
	double getEnthalpyFluxToDischargeChamberAverage();
	double getEnthalpyFluxToSuctionChamberAverage();
	double getEnthalpyFluxToInternalEnvironmentAverage();

	Refrigerant refrigerant;
	ExperimentalTemperatures expTemp;
	HeatTransfer heatTransfer;
	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;


protected:

	double enthalpyFluxToDischargeChamber;
	double enthalpyFluxToSuctionChamber;
	double enthalpyFluxToInternalEnvironment;
	double enthalpyFluxToDischargeChamberAverage;
	double enthalpyFluxToSuctionChamberAverage;
	double enthalpyFluxToInternalEnvironmentAverage;
	static string cylinder;
	double bore;
	double deadVolume;
	double length;
	double conicLength;
	double axisDistance;
	double volume;
	double displacementVolume;
	double derivateTemperature;
	static double derivateVolume;
	static double area;
};

#endif
