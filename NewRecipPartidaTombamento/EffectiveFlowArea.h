#ifndef EFFECTIVEFLOWAREA_H
#define EFFECTIVEFLOWAREA_H

#include "Input.h"
#include "NumericalRecipes.h"

class EffectiveFlowArea
{
public:
	EffectiveFlowArea();

	void calcSucEffectFlowArea(double cylPress, double sucChamberPress, double valvePosition);
	void calcDiscEffectFlowArea(double cylPress, double disChamberPress, double valvePosition);

	void setEffectFlowArea(vector<double> effectFlowAreaValue);
	void setEffectBackflowArea(vector<double> effectBackflowAreaValue);
	void setValveDisplacement(vector<double> valveDisplacementValue);

	double getSucEffectFlowArea();
	double getDisEffectFlowArea();

	void incrementId();

	static int id;
	
protected:
	VecDoub effectFlowArea;
	VecDoub effectBackflowArea;
	VecDoub valveDisplacement;
	static double effectSucArea;
	static double effectDisArea;
	
};

#endif
