#ifndef EFFECTIVEFORCEAREA_H
#define EFFECTIVEFORCEAREA_H

#include "Input.h"
#include "NumericalRecipes.h"

class EffectiveForceArea
{
public:
	EffectiveForceArea();

	void calcSucEffectForceArea(double cylPress, double sucChamberPress, double valvePosition);
	void calcDisEffectForceArea(double cylPress, double disChamberPress, double valvePosition);

	void setEffectForceArea(vector<double> effectForceAreaValue);
	void setBackflowEffectForceArea(vector<double> backflowEffectForceAreaValue);
	void setValveDisplacement(vector<double> valveDisplacementValue);
	
	double getEffectSucArea();
	double getEffectDisArea();

	void incrementId();

	static int id;
	
protected:
	VecDoub effectForceArea;
	VecDoub backflowEffectForceArea;
	VecDoub valveDisplacement;
	static double effectSucArea;
	static double effectDisArea;
	
};

#endif
