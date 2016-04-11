#include "EffectiveForceArea.h"

double EffectiveForceArea::sucEffForArea = 0;

double EffectiveForceArea::disEffForArea = 0;

EffectiveForceArea::EffectiveForceArea()
{
	
}

void EffectiveForceArea::calcSucEffForArea(double compChambPress, double sucChambPress, double valvePos)
{	
	sucEffForArea = 0;

	Spline_interp static flow(valveDisp,effForArea);

	Spline_interp static backFlow(valveDisp,backfEffForArea);

	if(compChambPress <= sucChambPress)
	{
		sucEffForArea = flow.interp(valvePos);
	}
	else
	{
		sucEffForArea = backFlow.interp(valvePos);
	}
}

void EffectiveForceArea::calcDisEffForArea(double compChambPress, double disChambPress, double valvePos)
{
	disEffForArea = 0;

	Spline_interp static flow(valveDisp,effForArea);

	Spline_interp static backFlow(valveDisp,backfEffForArea);

	if(compChambPress >= disChambPress)
	{
		disEffForArea = flow.interp(valvePos);
	}
	else
	{
		disEffForArea = backFlow.interp(valvePos);
	}
}

void EffectiveForceArea::setEffForArea(vector<double> effForAreaVal)
{
	effForArea.resize(effForAreaVal.size());

	for(int i = 0; i < effForAreaVal.size(); i++)
	{
		effForArea[i] = effForAreaVal[i]; 
	}
}

void EffectiveForceArea::setBackfEffForArea(vector<double> backfEffForAreaVal)
{
	backfEffForArea.resize(backfEffForAreaVal.size());

	for(int i = 0; i <  backfEffForAreaVal.size(); i++)
	{
		backfEffForArea[i] = backfEffForAreaVal[i]; 
	}
}

void EffectiveForceArea::setValveDisp(vector<double> valveDispVal)
{
	valveDisp.resize(valveDispVal.size());

	for(int i = 0; i < valveDispVal.size(); i++)
	{
		valveDisp[i] = valveDispVal[i]; 
	}
}

void EffectiveForceArea::setPointNum(double pointNumVal)
{
	pointNum = pointNumVal;
}

double EffectiveForceArea::getPointNum()
{
	return pointNum;
}

double EffectiveForceArea::getSucEffForArea()
{
	return sucEffForArea;
}

double EffectiveForceArea::getDisEffForArea()
{
	return disEffForArea;
}











