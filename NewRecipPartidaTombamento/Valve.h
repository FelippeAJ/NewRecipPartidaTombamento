#ifndef VALVE_H
#define VALVE_H

#include <cmath>
#include "Constants.h"
#include "EffectiveForceArea.h"
#include "SimulationParameters.h"

class Valve
{
public:
	Valve();

	void calcValveEquivMass();
	void calcEquivMass();

	void calcPreTensForAct();

	void calcSucStickForAct(int stickForId);
	void calcSucResultFor(double compChambPres, double sucChambPres);
	void calcSucAccel();
	void calcSucDisp();
	void calcSucVel();

	void calcDisStickForAct();
	void calcDisResultFor(double compChambPres, double disChambPres);
	void calcDisAccel();
	void calcDisDisp();
	void calcDisVel();

	double getResultFor();
	double getAccel();
	double getVel();
	double getDisp();

	void incremId();

	static int  id;
	int cont;

	EffectiveForceArea		effForArObj;
	SimulationParameters	simulPar;
 
//protected:
	int	   valveNum;
	double valveStickFor;
	double valvePreTens;
	double valveNatFreq;
	double valveStiff;
	double valveDamp;
	double valveEquivMass;	
	double natFreq;
	double stiff;
	double equivMass;
	double stickForAct;
	double preTensAct;
	double resultFor;
	double disp;
	double vel;
	double accel;
	double boostHeight;
	double impelHeight;
	double impelPreTens;
	double stopHeight;

};

#endif