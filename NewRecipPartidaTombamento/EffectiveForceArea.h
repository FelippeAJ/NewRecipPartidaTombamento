#ifndef EFFECTIVEFORCEAREA_H
#define EFFECTIVEFORCEAREA_H

#include "POLOIO.h"
#include "NumericalRecipes.h"

class EffectiveForceArea
{
public:
	EffectiveForceArea();

	void calcSucEffForArea(double compChambPress, double sucChambPress, double valvePos);
	void calcDisEffForArea(double compChambPress, double disChambPress, double valvePos);

	void setEffForArea(vector<double> effForAreaVal);
	void setBackfEffForArea(vector<double> backfEffForAreaVal);
	void setValveDisp(vector<double> valveDispVal);
	void setPointNum(double pointNUmber);
	
	double getSucEffForArea();
	double getDisEffForArea();
	double getPointNum();

protected:
	VecDoub effForArea;
	VecDoub backfEffForArea;
	VecDoub valveDisp;
	static double sucEffForArea;
	static double disEffForArea;
	double pointNum;
	
};

#endif
