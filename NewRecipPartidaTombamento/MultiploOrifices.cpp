#include "MultipleOrifices.h"

MultipleOrifices::MultipleOrifices()
{
	Input reader;
	reader.contOrificesNumber();

	numberOfOrifices = reader.getOrificesNumber();
}

void MultipleOrifices::creatMultipleOrifices()
{
	orificeFact.creatOrifice();
	dynSystemFact.creatDynamicSystem();
}

void MultipleOrifices::calcInicialProperties(double sucChamberSpecificHeatsRatio, double disChamberSpecificHeatsRatio)
{
	for(int i = 0; i < numberOfOrifices; i++)
	{
		dynSystemFact.dynamicSystem[i].calcEquivalentMass();
		dynSystemFact.dynamicSystem[i].valve.calcEquivalentMass();
	}

	orificesSet.calcSpecificHeatsRatioMedia(sucChamberSpecificHeatsRatio, disChamberSpecificHeatsRatio);
	orificesSet.calcCriticPress();

}

void MultipleOrifices::calcValveDynamic(double compressionChamberPressure, SuctionChamber sucChamberObj, DischargeChamber disChamberObj, int stickingForceIndice)
{
	for(int i = 0; i < numberOfOrifices; i++)
	{
		
		dynSystemFact.dynamicSystem[i].calcStickingForceAct(stickingForceIndice, orificeFact.orifice[i].getDirection());
		dynSystemFact.dynamicSystem[i].calcPreTensionForceAct();

		if(orificeFact.orifice[i].getDirection() == "suction")
		{
			dynSystemFact.dynamicSystem[i].effectForceAreaObj.calcSucEffectForceArea(compressionChamberPressure, sucChamberObj.refrigerant.getPressure(), dynSystemFact.dynamicSystem[i].getDisplacement()); 
		}
		else
		{
			dynSystemFact.dynamicSystem[i].effectForceAreaObj.calcDisEffectForceArea(compressionChamberPressure, disChamberObj.refrigerant.getPressure(),dynSystemFact.dynamicSystem[i].getDisplacement());
		}
	
		dynSystemFact.dynamicSystem[i].calcResultantForce(compressionChamberPressure, sucChamberObj.refrigerant.getPressure(), disChamberObj.refrigerant.getPressure(), orificeFact.orifice[i].getDirection());
		dynSystemFact.dynamicSystem[i].calcAccelaration();	
	}
}

void MultipleOrifices::calcMassFlow(double compressionChamberPressure, double compressionChamberTemperature, SuctionChamber sucChamberObj, DischargeChamber disChamberObj)
{
	for(int i = 0; i < numberOfOrifices; i++)
	{	

		if(dynSystemFact.dynamicSystem[i].getDisplacement() > 0)
		{
			orificesSet.calcPressRatio(compressionChamberPressure, sucChamberObj.refrigerant.getPressure(), disChamberObj.refrigerant.getPressure());
			orificesSet.calcUpstreamTemp(compressionChamberTemperature, sucChamberObj.refrigerant.getTemperature(), disChamberObj.refrigerant.getTemperature(), compressionChamberPressure, sucChamberObj.refrigerant.getPressure(), disChamberObj.refrigerant.getPressure());
			orificesSet.calcUpstreamPress(compressionChamberPressure, sucChamberObj.refrigerant.getPressure(), disChamberObj.refrigerant.getPressure());

			if(orificeFact.orifice[i].getDirection() == "suction")
			{
				orificeFact.orifice[i].effectFlowAreaObj.calcSucEffectFlowArea(compressionChamberPressure, sucChamberObj.refrigerant.getPressure(), dynSystemFact.dynamicSystem[i].getDisplacement());  
				orificeFact.orifice[i].calcMassFlow(refrigerant.getGasConstant(), orificesSet.getSpecificHeatsRatioMedia(), orificesSet.getSucUpstreamTemp(), orificesSet.getSucPressRatio(), orificesSet.getSucUpstreamPress());
				orificeFact.orifice[i].calcFlow();

				orificesSet.calcTotalSucMassFlow(orificeFact.orifice[i].getMassFlow());
				orificesSet.calcTotalSucFlux(orificeFact.orifice[i].getFlux());
				orificesSet.calcTotalSucBackflow(orificeFact.orifice[i].getBackFlow());
			}
			else
			{
				orificeFact.orifice[i].effectFlowAreaObj.calcDiscEffectFlowArea(compressionChamberPressure, disChamberObj.refrigerant.getPressure(), dynSystemFact.dynamicSystem[i].getDisplacement());
				orificeFact.orifice[i].calcMassFlow(refrigerant.getGasConstant(), orificesSet.getSpecificHeatsRatioMedia(), orificesSet.getDisUpstreamTemp(), orificesSet.getDisPressRatio(), orificesSet.getDisUpstreamPress());									
				orificeFact.orifice[i].calcFlow();

				orificesSet.calcTotalDisMassFlow(orificeFact.orifice[i].getMassFlow());
				orificesSet.calcTotalDisFlux(orificeFact.orifice[i].getFlux());
				orificesSet.calcTotalDisBackflow(orificeFact.orifice[i].getBackFlow());
			}
		}
	}
}

int MultipleOrifices::getNumberOfOrifices()
{
	return numberOfOrifices;
}

void MultipleOrifices::setNumberOfOrifices(int numberOfOrificesValue)
{
	numberOfOrifices = numberOfOrificesValue;
}

