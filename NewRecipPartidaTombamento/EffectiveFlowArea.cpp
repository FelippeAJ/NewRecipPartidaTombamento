#include "EffectiveFlowArea.h"

int EffectiveFlowArea::id = 0;

double EffectiveFlowArea::effectSucArea = 0;

double EffectiveFlowArea::effectDisArea = 0;

EffectiveFlowArea::EffectiveFlowArea()
{
	/*
	Input effectFlowAreaReader;

	effectFlowAreaReader.contOrificesNumber();

	effectFlowAreaReader.dimensionEffectFlowAreaVector();

	effectFlowAreaReader.contEffectFlowAreaPointsNumber();

	effectFlowAreaReader.dimensionEffectFlowAreaMatrix();

	effectFlowAreaReader.readEffectFlowArea();

	setEffectFlowArea(effectFlowAreaReader.getEffectFlowAreaData(id));

	setEffectBackflowArea(effectFlowAreaReader.getEffectiveBackFlowAreaData(id));

	setValveDisplacement(effectFlowAreaReader.getValveDisplacementData(id));

	*/
}

void EffectiveFlowArea::setEffectFlowArea(vector<double> effectFlowAreaValue)
{
	int cont = 0;

	for(int i = 1; i < effectFlowAreaValue.size(); i++)
	{
		if(effectFlowAreaValue[i] != 0)
		{
			cont++;
		}
	}
	
	effectFlowArea.resize(cont + 1);

	for(int i = 0; i < effectFlowArea.size(); i++)
	{
		effectFlowArea[i] = effectFlowAreaValue[i]; 
	}
}

void EffectiveFlowArea::setEffectBackflowArea(vector<double> effectBackflowAreaValue)
{
	int cont = 0;

	for(int i = 1; i < effectBackflowAreaValue.size(); i++)
	{
		if(effectBackflowAreaValue[i] != 0)
		{
			cont++;
		}
	}
	
	effectBackflowArea.resize(cont + 1);

	for(int i = 0; i < effectBackflowArea.size(); i++)
	{
		effectBackflowArea[i] = effectBackflowAreaValue[i]; 
	}
}

void EffectiveFlowArea::setValveDisplacement(vector<double> valveDisplacementValue)
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

double EffectiveFlowArea::getSucEffectFlowArea()
{
	return effectSucArea;
}

double EffectiveFlowArea::getDisEffectFlowArea()
{
	return effectDisArea;
}

void EffectiveFlowArea::incrementId()
{
	++id;
}

void EffectiveFlowArea::calcSucEffectFlowArea(double cylPress, double sucChamberPress, double valvePosition)
{	
	effectSucArea = 0;

	Spline_interp static flow(valveDisplacement,effectFlowArea);

	Spline_interp static backFlow(valveDisplacement,effectBackflowArea);

	if(cylPress <= sucChamberPress)
	{
		effectSucArea = flow.interp(valvePosition);
	}
	else
	{
		effectSucArea = -backFlow.interp(valvePosition);
	}
}

void EffectiveFlowArea::calcDiscEffectFlowArea(double cylPress, double disChamberPress, double valvePosition)
{
	effectDisArea = 0;

	Spline_interp static flow(valveDisplacement,effectFlowArea);

	Spline_interp static backFlow(valveDisplacement,effectBackflowArea);

	if(cylPress >= disChamberPress)
	{
		effectDisArea = flow.interp(valvePosition);
	}
	else
	{
		effectDisArea = -backFlow.interp(valvePosition);
	}
}








