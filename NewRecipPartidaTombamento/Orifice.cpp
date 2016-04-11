#include "Orifice.h"

int Orifice::id = 0;

Orifice::Orifice()
{
	Input orificeReaderData;

	orificeReaderData.contOrificesNumber();

	if(id >= orificeReaderData.getOrificesNumber())
	{
		id = 0;
	}

	orificeReaderData.dimensionOrificeVector();

	orificeReaderData.dimensionEffectFlowAreaVector();
	orificeReaderData.contEffectFlowAreaPointsNumber();
	orificeReaderData.dimensionEffectFlowAreaMatrix();
	orificeReaderData.readEffectFlowArea();
	effectFlowAreaObj.setEffectFlowArea(orificeReaderData.getEffectFlowAreaData(id));
	effectFlowAreaObj.setEffectBackflowArea(orificeReaderData.getEffectiveBackFlowAreaData(id));
	effectFlowAreaObj.setValveDisplacement(orificeReaderData.getValveDisplacementData(id));

	orificeReaderData.readOrificeData();

	setDirection(orificeReaderData.getOrificeDirection(id));

	incrementId();

	massFlow = 0;
	flux = 0;
	backflow = 0;
	massSumFlux = 0;
	energySumFlux = 0;
	massSumBackflow = 0;
}

void Orifice::calcMassFlow(double gasConst, double specificHeatsRatioMedia, double upstreamTemp, double pressRatio, double  upstreamPress)
{
	double A = (2*specificHeatsRatioMedia)/((specificHeatsRatioMedia -1)*gasConst*upstreamTemp);

	double B = pow(pressRatio,(2/specificHeatsRatioMedia)) - pow(pressRatio,(specificHeatsRatioMedia + 1)/specificHeatsRatioMedia);

	if(direction == "suction")
	{
		massFlow = effectFlowAreaObj.getSucEffectFlowArea() * upstreamPress * sqrt(A) * sqrt(B);
	}
	else
	{
		massFlow = effectFlowAreaObj.getDisEffectFlowArea() * upstreamPress * sqrt(A) * sqrt(B);
	}
}

void Orifice::calcFlow()
{
	if(massFlow >= 0)
	{
		flux = massFlow;
		backflow = 0;
	}
	else
	{
		flux = 0;
		backflow = -massFlow;
	}
}

void Orifice::calcMassSum(double timeStep)
{
	if(massFlow > 0)
	{
		massSumFlux += massFlow*timeStep;
	}
	else
	{
		massSumBackflow = massSumBackflow - massFlow*timeStep;
	}
}

void Orifice::calcEnergySum(double timeStep, double enthalpy)
{
	if(massFlow > 0)
	{
		energySumFlux += energySumFlux*enthalpy*timeStep;
	}
	else
	{
		energySumBackflow = energySumBackflow - massFlow*enthalpy*timeStep;
	}


}

void Orifice::calcSuperheatingMassLoses(double suctionChamberRho, double cylinderRho, double timeStep)
{
	if(direction == "suction")
	{
		if(massFlow > 0)
		{
			superheatingMassLoses += massFlow*(suctionChamberRho/cylinderRho - 1)*timeStep;
		}
	}
}

void Orifice::setDirection(string directionName)
{
	direction = directionName;
}

void Orifice::setMassFlow(double massFlowValue)
{
	massFlow = massFlowValue;
}

string Orifice::getDirection()
{
	return direction;
}

double Orifice::getMassFlow()
{
	return massFlow;
}


double Orifice::getFlux()
{
	return flux;
}

double Orifice::getBackFlow()
{
	return backflow;
}

double Orifice::getMassSumFlux()
{
	return massSumFlux;
}

double Orifice::getMassSumBackflow()
{
	return massSumBackflow;
}

void Orifice::incrementId()
{
	++id;
}




