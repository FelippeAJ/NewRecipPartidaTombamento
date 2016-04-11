#include "Work.h"

Work::Work()
{
	inicialIteration = 0;
	refrigerantWork = 0;
	totalSucValveWork = 0;
	totalDisValveWork = 0;
	totalSucChamberWork = 0;
	totalDisChamberWork = 0;
	leakWork = 0;
	
}

void Work::setInicialProperties(double inicialPressureValue, double inicialVolumeValue)
{
	if(inicialIteration == 0)
	{
		oldWorkPressure = inicialPressureValue;
		oldWorkVolume = inicialVolumeValue;
		inicialIteration = 1;
	}
}

void Work::setWorkPres(double workPresValue)
{
	workPressure = workPresValue;
}

void Work::setWorkVol(double workVolValue)
{
	workVolume = workVolValue;
}

void Work::setOldWorkPres(double presValue)
{
	oldWorkPressure = presValue;
}

void Work::setOldWorkVol(double volValue)
{
	oldWorkVolume = volValue;
}

void Work::calcWorkMediaPres()
{
	workMediaPressure = (oldWorkPressure + workPressure)/2;
}

void Work::calcRefrigerantWork()
{
	refrigerantWork += (oldWorkVolume - workVolume)*workMediaPressure;
}

void Work::calcSucValveWork(double sucLinePres, double sucChamberPres)
{
	if(workPressure < sucLinePres)
	{
		sucValveWork = (workVolume - oldWorkVolume)*(sucChamberPres - workMediaPressure);
		totalSucValveWork += sucValveWork;
	}
	else
	{
		sucValveWork = 0;
	}

	termo1 = (workVolume - oldWorkVolume);
	termo2 = sucChamberPres;
	termo3 =  workMediaPressure;
	termo4 = (sucChamberPres - workMediaPressure);
}

void Work::calcDisValveWork(double disLinePres, double disChamberPres)
{
	if(workPressure > disLinePres)
	{
		disValveWork = (oldWorkVolume - workVolume)*(workMediaPressure - disChamberPres);
		totalDisValveWork += disValveWork;
	}
	else
	{
		disValveWork = 0;
	}
}

void Work::calcSucChamberWork(double sucLinePres, double sucChamberPres)
{
	if(workPressure < sucLinePres)
	{
		sucChamberWork = (workVolume - oldWorkVolume)*(sucLinePres - sucChamberPres);
		totalSucChamberWork += sucChamberWork;
	}
	else
	{
		sucChamberWork = 0; 
	}
}

void Work::calcDisChamberWork(double disLinePres, double disChamberPres)
{
	if(workPressure > disLinePres)
	{
		disChamberWork = (oldWorkVolume - workVolume)*(disChamberPres - disLinePres);
		totalDisChamberWork += disChamberWork;
	}
	else
	{
		disChamberWork = 0;
	}
}

void Work::calcLeakWork(double cylinderRho, double cylinderTemp, double leakMassFlow, double timeStep)
{
	refrig.setTemp(cylinderTemp);

	refrig.setRho(cylinderRho);

	refrig.calcSpecHeat();

	leakWork += leakMassFlow*timeStep*(refrig.getCp() - refrig.getCv())*cylinderTemp;
}

double Work::getRefrigerantWork()
{
	return refrigerantWork;
}

double Work::getSuctionValveWork()
{
	return totalSucValveWork;
}

double Work::getDischargeValveWork()
{
	return totalDisValveWork;
}

double Work::getSucChamberWork()
{
	return totalSucChamberWork;
}

double Work::getDisChamberWork()
{
	return totalDisChamberWork;
}

double Work::getLeakWork()
{
	return leakWork;
}
