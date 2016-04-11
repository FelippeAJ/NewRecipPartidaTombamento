#include "DynamicSystem.h"

int DynamicSystem::id = 0;

DynamicSystem::DynamicSystem()
{
	double stickingForceAct = 0;
	double preTensionAct = 0;
	double stickingForce = 0;

	Input dynamicSystReaderData;

	dynamicSystReaderData.contOrificesNumber();

	if(id >= dynamicSystReaderData.getOrificesNumber())
	{
		id = 0;
	}

	dynamicSystReaderData.dimensionDynamicSystemVector();

	dynamicSystReaderData.readDynamicSystemData();

	dynamicSystReaderData.dimensionEffectForceAreaVector();
	
	dynamicSystReaderData.contEffectForceAreaPointsNumber();

	dynamicSystReaderData.dimensionEffectForceAreaMatrix();

	dynamicSystReaderData.readEffectForceArea();

	effectForceAreaObj.setEffectForceArea(dynamicSystReaderData.getEffectForceAreaData(id));

	effectForceAreaObj.setBackflowEffectForceArea(dynamicSystReaderData.getBackFlowEffectiveForceAreaData(id));

	effectForceAreaObj.setValveDisplacement(dynamicSystReaderData.getEffectForceAreaValveDisplacementData(id));

	setStickingForce(dynamicSystReaderData.getStickingForce(id));

	setNatFrequency(dynamicSystReaderData.getDynSystNatFrequency(id));

	setStiffness(dynamicSystReaderData.getDynSystStiffness(id));

	impeller.setHeight(dynamicSystReaderData.getImpellerHeight(id));

	impeller.setPreTension(dynamicSystReaderData.getImpellerPreTension(id));

	valve.setNatFrequency(dynamicSystReaderData.getValveNatFrequency(id));

	valve.setDamping(dynamicSystReaderData.getValveDamping(id));

	valve.setStiffness(dynamicSystReaderData.getValveStiffness(id));

	valve.setPreTension(dynamicSystReaderData.getValvePreTension(id));

	booster.setHeight(dynamicSystReaderData.getBoosterHeight(id));

	stopper.setHeight(dynamicSystReaderData.getStopperHeight(id));

	displacement = 0;

	velocity = 0;

	accelaration = 0;

	incrementId();
}

void DynamicSystem::calcEquivalentMass()
{
	Constants cte;

	equivalentMass = stiffness/pow((2*cte.Pi*natFrequency),2);
}

void DynamicSystem::calcStickingForceAct(int stickingForceIndice, string direction)
{
	if(direction == "suction")
	{
		if(displacement == 0 && stickingForceIndice == 1)
		{
			
				stickingForceAct = stickingForce;

		}
		else
			stickingForceAct = 0;
	}
	else
	{
		if(direction == "discharge" && displacement <= 0)
			stickingForceAct = stickingForce;
		else
			stickingForceAct = 0;
	}
}

void DynamicSystem::calcPreTensionForceAct()
{
	if(impeller.getHeight() == 0)			
	{	
		preTensionAct = valve.getPreTension();
	}
	
	if(displacement > impeller.getHeight() && impeller.getHeight() != 0)
	{
		preTensionAct = 0;
	}
	else 
	if(displacement < impeller.getHeight() && impeller.getHeight() != 0)
	{
		preTensionAct = impeller.getPreTension()*(impeller.getHeight() - displacement)/impeller.getHeight();
	}
}

void DynamicSystem::calcResultantForce(double cylPress, double sucChamberPress, double disChamberPress, string orificeDirecion)
{
	if(orificeDirecion == "suction")
	{
		resultantForce = (sucChamberPress - cylPress)*effectForceAreaObj.getEffectSucArea() - preTensionAct - stickingForceAct;
	}
	else
	{
		resultantForce = (cylPress - disChamberPress)*effectForceAreaObj.getEffectDisArea() - preTensionAct - stickingForceAct;
	}
}

void DynamicSystem::calcDisplacement()
{	
	if(displacement == 0 && resultantForce > 0 || displacement > 0)
	{
		displacement += velocity*simulParameters.getTimeStep();	
	}

	if(displacement < 0)
	{
		displacement  = 0;
		velocity = 0;
	}

	if(displacement > stopper.getHeight() && stopper.getHeight() != 0)
	{
		displacement = stopper.getHeight();
		velocity = 0;
	}
}

void DynamicSystem::calcVelocity()
{
	velocity += accelaration*simulParameters.getTimeStep();
	/*
	if(displacement < 0)
		velocity = 0;
	
	if(displacement > stopper.getHeight() && stopper.getHeight() != 0)
		velocity = 0;
	*/
}

void DynamicSystem::calcAccelaration()
{
	Constants cte;

	if(displacement == 0 && resultantForce > 0 || displacement > 0)
	{
		if(displacement < booster.getHeight())
		{
			accelaration = resultantForce/valve.getEquivalentMass() -4*cte.Pi*valve.getDamping()*valve.getNatFrequency()*velocity - valve.getStiffness()/valve.getEquivalentMass()*displacement;
			
		}
		else
		{
			accelaration = resultantForce/equivalentMass -4*cte.Pi*valve.getDamping()*natFrequency*velocity - stiffness/equivalentMass*displacement;
		}

		

		calcVelocity();

		calcDisplacement();
	}
}

void DynamicSystem::setStickingForce(double stickingForceValue)
{
	stickingForce = stickingForceValue;
}

void DynamicSystem::setNatFrequency(double natFrequencyValue)
{
	natFrequency = natFrequencyValue;
}

void DynamicSystem::setStiffness(double stiffnessValue)
{
	stiffness = stiffnessValue;
}

double DynamicSystem::getResultantForce()
{
	return resultantForce;
}

double DynamicSystem::getAccelaration()
{
	return  accelaration;
}

double DynamicSystem::getVelocity()
{
	return velocity;
}

double DynamicSystem::getDisplacement()
{
	return displacement;
}

void DynamicSystem::incrementId()
{
	++id;
}






















































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































 


