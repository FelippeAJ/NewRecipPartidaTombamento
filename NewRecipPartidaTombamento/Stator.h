#ifndef STATOR_H
#define STATOR_H

#include <cmath>
#include "Constants.h"
#include "Input.h"
#include "Axis.h"
#include "Motor.h"
#include <complex>

class Stator
{
public:
	Stator();

	void setMainWindingReferenceResistance(double mainWindingReferenceResistanceValue);
	void setThermalCoefficient(double thermalCoefficientValue);
	void setReferenceTemperature(double referenceTemperatureValue);
	void setMainWindingReactance(double mainWindingReactanceValue);
	void setMagnetizingReactance(double magnetizingReactanceValue);
	void setIronResistance(double ironResistanceValue);

	void calcMainWindingResistance(double thermalCoefficient, double referenceTemperature, double mainWindingReferenceResistance, double motorTemperature);
	void calcMainWindingImpedance(double mainWindingResistance, double mainWindingReactance);
	void calcPositiveMagnetizingImpedance(double magnetizingReactance);
	void calcNegativeMagnetizingImpedance(double magnetizingReactance);
	void calcPositiveIronImpedance(double ironResistance);
	void calcNegativeIronImpedance(double ironResistance);
	void calcMainWindingCurrent(double inputVoltage, double equivalentImpedanceMagnitude);
	void calcPositiveIronCurrent(double positiveImpedance, double mainWindingCurrent, double positiveIronImpedance);
	void calcNegativeIronCurrent(double negativeImpedance, double mainWindingCurrent, double negativeIronImpedance);

	complex<double> getMainWindingImpedance();
	double getPositiveMagnetizingImpedance();
	double getNegativeMagnetizingImpedance();
	double getPositiveIronImpedance();
	double getNegativeIronImpedance();
	double getMainWindingCurrent();
	double getPositiveIronCurrent();
	double getNegativeIronCurrent();

	Axis axis;
	Motor motor;
	Constants cte;

protected:
	complex<double> mainWindingImpedance;
	complex<double> positiveMagnetizingImpedance;
	complex<double> negativeMagnetizingImpedance;
	complex<double> positiveIronImpedance;
	complex<double> negativeIronImpedance;
	double mainWindingCurrent;
	double positiveIronCurrent;
	double negativeIronCurrent;
};

#endif

