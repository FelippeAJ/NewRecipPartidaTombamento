#ifndef EFFECTIVEFLOWAREA_H
#define EFFECTIVEFLOWAREA_H

#include "POLOIO.h"
#include "NumericalRecipes.h"

class EffectiveFlowArea
{
public:
	EffectiveFlowArea();

	void calcSucEffFlArea(double compChambPress, double sucChambPress, double valvePos);
	void calcDisEffFlArea(double compChambPress, double disChambPress, double valvePos);

	void setEffFlArea(vector<double> effFlAreaVal);
	void setBackfEffFlArea(vector<double> backflEffFlAreaVal);
	void setValveDisp(vector<double> valveDispVal);
	void setPointNum(double pointNumVal);

	double getSucEffFlArea();
	double getDisEfftFlArea();
	double getPointNum();

//protected:
	VecDoub effFlArea;
	VecDoub backfeffFlArea;
	VecDoub valveDisp;
	static double sucEffFlArea;
	static double disEffFlArea;
	double pointNum;
};

#endif
