#include "AnnulusLeak.h"

AnnulusLeak::AnnulusLeak()
{
	Input annulusLeakReaderData;

	annulusLeakReaderData.readAnnulusLeakData();

	setSucMaxArea(annulusLeakReaderData.getAnnulusLeakSucMaxArea());

	setSucMinArea(annulusLeakReaderData.getAnnulusLeakSucMinArea());

	setSucDeltaPressure(annulusLeakReaderData.getAnnulusLeakSucDeltaPressure());

	setSucCorrectionCoef(annulusLeakReaderData.getAnnulusLeakSucCorrecCoef());

	setDisMaxArea(annulusLeakReaderData.getAnnulusLeakDisMaxArea());

	setDisMinArea(annulusLeakReaderData.getAnnulusLeakDisMinArea());

	setDisDeltaPressure(annulusLeakReaderData.getAnnulusLeakDisDeltaPressure());

	setDisCorrectionCoef(annulusLeakReaderData.getAnnulusLeakDisCorrecCoef());

	sucMassFlow = 0;
	disMassFlow = 0;

}

void AnnulusLeak::calcSucArea(double cylPress, double sucChamberPress)
{
	sucArea = ((sucMinArea - sucMaxArea)/sucDeltaPressure)*(cylPress - sucChamberPress) + sucMaxArea;

	if(sucArea < 0)
	{
		sucArea = 0;
	}
}

void AnnulusLeak::calcDisArea(double cylPress, double disChamberPress)
{
	disArea = ((disMinArea - disMaxArea)/disDeltaPressure)*(disChamberPress - cylPress) + disMaxArea;

	if(disArea < 0)
	{
		disArea = 0;
	}
}

//void AnnulusLeak::calcSucMassFlow(double cylPress, double sucChamberPress, double cylRho, double orificesNumber ,DynamicSystemFactory dynSystemFact)
//{
//	for(int i = 0; i < orificesNumber; i++)
//	{
//		if(orificeFact.orifice[i].getDirection() == "suction")
//		{
//			if(dynSystemFact.dynamicSystem[i].getDisplacement == 0 && cylPress > sucChamberPress)
//			{
//				sucMassFlow = sucCorrectionCoeficient*sucArea*sqrt((2*cylRho*(cylPress - sucChamberPress));
//			}
//			else
//			{
//				sucMassFlow = 0;
//			}
//		}
//	}
//}

//void AnnulusLeak::calcDisMassFlow(double cylPress, double disChamberPress, double disChamberRho, double orificesNumber ,DynamicSystemFactory dynSystemFact)
//{
//	for(int i = 0; i < orificesNumber; i++)
//	{
//		if(orificeFact.orifice[i].getDirection() == "discharge")
//		{
//			if(dynSystemFact.dynamicSystem[i].getDisplacement == 0 && disChamberPress > cylPress)
//			{
//				disMassFlow = disCorrectionCoeficient*disArea*sqrt((2*disChamberRho*(cylPress - disChamberPress));
//			}
//			else
//			{
//				disMassFlow = 0;
//			}
//		}
//	}
//}

void AnnulusLeak::setSucMaxArea(double sucMaxAreaValue)
{
	sucMaxArea = sucMaxAreaValue;
}

void AnnulusLeak::setSucMinArea(double sucMinAreaValue)
{
	sucMinArea = sucMinAreaValue;
}

void AnnulusLeak::setSucDeltaPressure(double sucDeltaPressureValue)
{
	sucDeltaPressure = sucDeltaPressureValue;
}

void AnnulusLeak::setSucCorrectionCoef(double sucCorrectCoefValue)
{
	sucCorrectionCoeficient = sucCorrectCoefValue;
}

void AnnulusLeak::setDisMaxArea(double disMaxAreaValue)
{
	disMaxArea = disMaxAreaValue;
}

void AnnulusLeak::setDisMinArea(double disMinAreaValue)
{
	disMinArea = disMinAreaValue;
}

void AnnulusLeak::setDisDeltaPressure(double disDeltaPressureValue)
{
	disDeltaPressure = disDeltaPressureValue;
}

void AnnulusLeak::setDisCorrectionCoef(double disCorrectCoefValue)
{
	disCorrectionCoeficient = disCorrectCoefValue;
}

double AnnulusLeak::getSucMassFlow()
{
	return sucMassFlow;
}

double AnnulusLeak::getDisMassFlow()
{
	return disMassFlow;
}