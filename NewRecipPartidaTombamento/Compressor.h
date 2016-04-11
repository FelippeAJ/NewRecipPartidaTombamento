#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include "Constants.h"
#include "POLOIO.h"
#include "Refrigerant.h"
#include "Mechanism.h"
#include "Bearings.h"
#include "CompressionChamber.h"
#include "Leak.h"
#include "SuctionSystem.h"
#include "OrificeFactory.h"
#include "DischargeSystem.h"
#include "System.h"
#include "Motor.h"
#include "Work.h"
#include "PostProcessing.h"
#include "SimulationParameters.h"

using namespace std;

class Compressor 
{
public:
	Compressor();
	void silmulComp();
	void calcMechanIniProp();
	void calcLeak();
	void calcSimulPar();
	void calcWork();
	void execPostProc(ofstream &outputData);
	void expResult(ofstream &expData); 

	Constants				ct;
	Refrigerant				refrigObj;
	Mechanism				mechanObj;
	Bearings				bearObj;
	CompressionChamber		compChambObj;
	Leak					leakObj;
	SuctionSystem			sucSystObj;
	DischargeSystem			disSystObj;
	System					systObj;
	Motor					motObj;
	Work					workObj;
	SimulationParameters	simulParObj;
	PostProcessing			postProcObj;
	OrificeFactory			orifFacObj;




protected:

	int plotCont;
	int multip;
	int it;
	int cont;
	int n;

};

#endif;