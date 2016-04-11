#ifndef ORIFICE_H
#define ORIFICE_H

#include <cmath>
#include <iostream>
#include "EffectiveFlowArea.h"
#include "POLOIO.h"
#include "Refrigerant.h"

class Orifice
{
public:
	Orifice();

	void calcSucMassFl();
	void calcDisMassFl();
	void calcFl();
	void calcMassSum(double timeStep);

	void setMassFl(double massFlVal);
	
	string getDirection();
	double getSpecHeatRatMed();
	double getMassFl();
	double getFl();
	double getBackf();
	double getMassSumFl();
	double getMassSumBackf();

	void incremId();
	static int id;

	EffectiveFlowArea effFlAreaObj;

	void calcSpecHeatRatMed(double sucChambSpecHeatRat, double disChambSpecHeatRat);
	void calcCritPress();
	
	void calcSucUpTemp(double compChambTemp, double sucChambTemp, double compChambPress, double sucChambPress);
	void calcDisUpTemp(double compChambTemp, double disChambTemp, double compChambPress, double disChambPress);

	void calcSucUpPress(double compChambPress, double sucChambPress);
	void calcDisUpPress(double compChambPress, double disChambPress);

	void calcSucPressRat(double compChambPress, double sucChambPress);
	void calcDisPressRat(double compChambPress, double disChambPress);
	
	void calcTotSucMassFl(double sucMassFl);
	void calcTotSucFl(double sucFlux);
	void calcTotSucBackf(double sucBackflow);
	void calcTotDisMassFl(double disMassFlow);
	void calcTotDisFl(double disFlux);
	void calcTotDisBackf(double disBackflow);

	void setTotSucMassFl(double totSucMassFlVal);
	void setTotSucFl(double totSucFlVal);
	void setTotSucBackf(double totSucBackfVal);
	void setTotDisMassFl(double totDisMassFlVal);
	void setTotDisFl(double totDisFlVal);
	void setTotDisBackf(double totDisBackfVal);

	double getTotSucMassFl();
	double getTotSucFl();
	double getTotSucBackf();
	double getTotDisMassFl();
	double getTotDisFl();
	double getTotDisBackf();

	Refrigerant refrig;

//protected:

	string direction;
	double massFl;	
	double fl;
	double backf;

	double massSumFl;
	double enSumFl;
	double massSumBackf;
	double enSumBackf;
	double supheatMassLoss;

	double specHeatRatMed;
	double critPress;
	double sucUpTemp;
	double sucUpPress;
	double sucPressRat;
	double totSucMassFl;
	double totSucFl;
	double totSucBackf;
	double disUpTemp;
	double disUpPress;
	double disPressRat;
	double totDisMassFl;
	double totDisFl;
	double totDisBackf;
};

#endif