#ifndef WORK_H
#define WORK_H

#include "POLOIO.h"
#include "Refrigerant.h"

class Work
{
public:
	Work();

	void calcWorkMediaPres();
	void calcRefrigerantWork();
	void calcSucValveWork(double sucLinePres, double sucChamberPres);
	void calcDisValveWork(double disLinePres, double disChamberPres);
	void calcSucChamberWork(double sucLinePres, double sucChamberPres);
	void calcDisChamberWork(double disLinePres, double disChamberPres);
	void calcLeakWork(double cylinderRho, double cylinderTemp, double leakMassFlow, double timeStep);

	void setInicialProperties(double inicialPres, double inicialVol);
	void setWorkPres(double workPresValue);
	void setWorkVol(double workVolValue);
	void setOldWorkPres(double presValue);
	void setOldWorkVol(double volValue);

	double getRefrigerantWork();
	double getSuctionValveWork();
	double getDischargeValveWork();
	double getSucChamberWork();
	double getDisChamberWork();
	double getLeakWork();

	Refrigerant refrig;

	double sucValveWork;
	double disValveWork;
	double sucChamberWork;
	double disChamberWork;
	double termo1;
	double termo2;
	double termo3;
	double termo4;


protected:
	double workPressure;
	double workVolume;
	double oldWorkPressure;
	double oldWorkVolume;
	double workMediaPressure;
	double refrigerantWork;
	double totalSucValveWork;
	
	double totalDisValveWork;
	
	double totalSucChamberWork;
	
	double totalDisChamberWork;
	
	double leakWork;
	double inicialIteration;
};

#endif
