#include "EffectiveFlowArea.h"

double EffectiveFlowArea::sucEffFlArea = 0;

double EffectiveFlowArea::disEffFlArea = 0;

EffectiveFlowArea::EffectiveFlowArea()
{

}

void EffectiveFlowArea::calcSucEffFlArea(double compChambPress, double sucChambPress, double valvePos)
{	
	sucEffFlArea = 0;

	Spline_interp static flow(valveDisp, effFlArea);

	Spline_interp static backFlow(valveDisp, backfeffFlArea);

	if(compChambPress <= sucChambPress)
	{
		sucEffFlArea = flow.interp(valvePos);
	}
	else
	{
		sucEffFlArea = -backFlow.interp(valvePos);
	}

}

void EffectiveFlowArea::calcDisEffFlArea(double compChambPress, double disChambPress, double valvePos)
{
	disEffFlArea = 0;

	Spline_interp static flow(valveDisp, effFlArea);

	Spline_interp static backFlow(valveDisp, backfeffFlArea);

	if(compChambPress >= disChambPress)
	{
		disEffFlArea = flow.interp(valvePos);
	}
	else
	{
		disEffFlArea = -backFlow.interp(valvePos);
	}
}

void EffectiveFlowArea::setEffFlArea(vector<double> effFlAreaVal)
{
	effFlArea.resize(effFlAreaVal.size());

	for(int i = 0; i < effFlAreaVal.size(); i++)
	{
		effFlArea[i] = effFlAreaVal[i]; 
	}
}

void EffectiveFlowArea::setBackfEffFlArea(vector<double> backflEffFlAreaVal)
{
	backfeffFlArea.resize(backflEffFlAreaVal.size());

	for(int i = 0; i < backflEffFlAreaVal.size(); i++)
	{
		backfeffFlArea[i] = backflEffFlAreaVal[i]; 
	}
}

void EffectiveFlowArea::setValveDisp(vector<double> valveDispVal)
{	
	valveDisp.resize(valveDispVal.size());

	for(int i = 0; i < valveDispVal.size(); i++)
	{
		valveDisp[i] = valveDispVal[i]; 
	}
}

void EffectiveFlowArea::setPointNum(double pointNumVal)
{
	pointNum = pointNumVal;
}

double EffectiveFlowArea::getPointNum()
{
	return pointNum;
}

double EffectiveFlowArea::getSucEffFlArea()
{
	return sucEffFlArea;
}

double EffectiveFlowArea::getDisEfftFlArea()
{
	return disEffFlArea;
}







