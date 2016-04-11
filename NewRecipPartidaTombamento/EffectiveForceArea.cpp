#include "EffectiveForceArea.h"

int EffectiveForceArea::id = 0;

double EffectiveForceArea::effectSucArea = 0;

double EffectiveForceArea::effectDisArea = 0;

EffectiveForceArea::EffectiveForceArea()
{
	Input effectForceAreaReader;

	effectForceAreaReader.contOrificesNumber();

	effectForceAreaReader.dimensionEffectForceAreaVector();

	effectForceAreaReader.contEffectForceAreaPointsNumber();

	effectForceAreaReader.dimensionEffectForceAreaMatrix();

	effectForceAreaReader.readEffectForceArea();

	setEffectForceArea(effectForceAreaReader.getEffectForceAreaData(id));

	setBackflowEffectForceArea(effectForceAreaReader.getBackFlowEffectiveForceAreaData(id));

	setValveDisplacement(effectForceAreaReader.getEffectForceAreaValveDisplacementData(id));
	
}

void EffectiveForceArea::calcSucEffectForceArea(double cylPress, double sucChamberPress, double valvePosition)
{	
	effectSucArea = 0;

	Spline_interp static flow(valveDisplacement,effectForceArea);

	Spline_interp static backFlow(valveDisplacement,backflowEffectForceArea);

	if(cylPress <= sucChamberPress)
	{
		effectSucArea = flow.interp(valvePosition);
	}
	else
	{
		effectSucArea = backFlow.interp(valvePosition);
	}
}

void EffectiveForceArea::calcDisEffectForceArea(double cylPress, double disChamberPress, double valvePosition)
{
	effectDisArea = 0;

	Spline_interp static flow(valveDisplacement,effectForceArea);

	Spline_interp static backFlow(valveDisplacement,backflowEffectForceArea);

	if(cylPress >= disChamberPress)
	{
		effectDisArea = flow.interp(valvePosition);
	}
	else
	{
		effectDisArea = backFlow.interp(valvePosition);
	}
}

void EffectiveForceArea::setEffectForceArea(vector<double> effectForceAreaValue)
{
	int cont = 0;

	for(int i = 1; i < effectForceAreaValue.size(); i++)
	{
		if(effectForceAreaValue[i] != 0)
		{
			cont++;
		}
	}
	
	effectForceArea.resize(cont + 1);

	for(int i = 0; i < effectForceArea.size(); i++)
	{
		effectForceArea[i] = effectForceAreaValue[i]; 
	}
}

void EffectiveForceArea::setBackflowEffectForceArea(vector<double> backflowEffectForceAreaValue)
{
	int cont = 0;

	for(int i = 1; i < backflowEffectForceAreaValue.size(); i++)
	{
		if(backflowEffectForceAreaValue[i] != 0)
		{
			cont++;
		}
	}
	
	 backflowEffectForceArea.resize(cont + 1);

	for(int i = 0; i <  backflowEffectForceArea.size(); i++)
	{
		 backflowEffectForceArea[i] = backflowEffectForceAreaValue[i]; 
	}
}

void EffectiveForceArea::setValveDisplacement(vector<double> valveDisplacementValue)
{
	int cont = 0;

	for(int i = 1; i < valveDisplacementValue.size(); i++)
	{
		if(valveDisplacementValue[i] != 0)
		{
			cont++;
		}
	}
	
	valveDisplacement.resize(cont + 1);

	for(int i = 0; i < valveDisplacement.size(); i++)
	{
		valveDisplacement[i] = valveDisplacementValue[i]; 
	}
}

double EffectiveForceArea::getEffectSucArea()
{
	return effectSucArea;
}

double EffectiveForceArea::getEffectDisArea()
{
	return effectDisArea;
}

void EffectiveForceArea::incrementId()
{
	++id;
}








