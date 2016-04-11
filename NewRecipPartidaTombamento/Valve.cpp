#include "Valve.h"
#include "POLOIO.h"

int Valve::id = 0;

Valve::Valve()
{
	POLOIO POLOIOobj1("input.dat");
	string idStr = to_string(id);

	valveNum		=	POLOIOobj1.getParamVal("orifices_number", "left");
	impelPreTens	=	POLOIOobj1.getParamVal("orifice", idStr, "impeller_pretension", "left");
	impelHeight		=	POLOIOobj1.getParamVal("orifice", idStr, "impeller_height", "left");	
	valvePreTens	=	POLOIOobj1.getParamVal("orifice", idStr, "valve_pretension", "left");
	valveStickFor	=	POLOIOobj1.getParamVal("orifice", idStr, "valve_stickingforce", "left");
	valveNatFreq	=	POLOIOobj1.getParamVal("orifice", idStr, "valve_natfrequency", "left");
	valveStiff		=	POLOIOobj1.getParamVal("orifice", idStr, "valve_stiffness", "left");
	valveDamp		=	POLOIOobj1.getParamVal("orifice", idStr, "valve_damping", "left");
	boostHeight		=	POLOIOobj1.getParamVal("orifice", idStr, "booster_height", "left");
	stopHeight		=	POLOIOobj1.getParamVal("orifice", idStr, "stopper_height", "left");
	natFreq			=	POLOIOobj1.getParamVal("orifice", idStr, "natfrequency", "left");
	stiff			=	POLOIOobj1.getParamVal("orifice", idStr, "stiffness", "left");
	stopHeight		=	POLOIOobj1.getParamVal("orifice", idStr, "stopper_height", "left");

	POLOIO POLOIOobj2("AEF.dat");
	
	effForArObj.setPointNum(POLOIOobj2.getParamVal("orifice", idStr, "points_number", "left"));
	effForArObj.setValveDisp(POLOIOobj2.getColumnMatrix("orifice_data_matrix", idStr, "right", effForArObj.getPointNum() , 0));
	effForArObj.setEffForArea(POLOIOobj2.getColumnMatrix("orifice_data_matrix", idStr, "right", effForArObj.getPointNum() , 1));
	effForArObj.setBackfEffForArea(POLOIOobj2.getColumnMatrix("orifice_data_matrix", idStr, "right", effForArObj.getPointNum() , 2));

	disp			=	0;
	vel				=	0;
	accel			=	0;
	impelHeight		=	0;
	impelPreTens	=	0;
	valveStickFor	=	0;
	valvePreTens	=	0;
	stopHeight		=	0;
	stickForAct		=	0;
	preTensAct		=	0;
	
	incremId();
	cont  = 0;

	cout << "valveNatFreq   "  <<  id  << "   "  << valveNatFreq << endl;
}

void Valve::calcValveEquivMass()
{
	Constants cte;

	valveEquivMass = valveStiff/pow((2*cte.Pi*valveNatFreq),2);
}

void Valve::calcEquivMass()
{
	Constants cte;

	equivMass = stiff/pow((2*cte.Pi*natFreq),2);
}

void Valve::calcPreTensForAct()
{
	if(impelHeight == 0)			
	{	
		preTensAct = valvePreTens;
	}
	
	if(disp > impelHeight && impelHeight != 0)
	{
		preTensAct = 0;
	}
	else 
	if(disp < impelHeight && impelHeight != 0)
	{
		preTensAct = impelPreTens*(impelHeight - disp)/impelHeight;
	}
}

void Valve::calcSucStickForAct(int stickForId)
{
	if(disp == 0 && stickForId == 1)
	{
		stickForAct =  valveStickFor;
	}
	else
	{
		stickForAct = 0;
	}
}

void Valve::calcDisStickForAct()
{
	if(disp <= 0)
	{
		stickForAct = valveStickFor;
	}
	else
	{
		stickForAct = 0;
	}
}

void Valve::calcSucResultFor(double compChambPres, double sucChambPres)
{
	resultFor = (sucChambPres - compChambPres)*effForArObj.getSucEffForArea() - preTensAct - stickForAct;
}

void Valve::calcDisResultFor(double compChambPres, double disChambPres)
{
	resultFor = (compChambPres - disChambPres)*effForArObj.getDisEffForArea() - preTensAct - stickForAct;
}

void Valve::calcSucDisp()
{	
	if(disp == 0 && resultFor > 0 || disp > 0)
	{
		disp += vel*simulPar.getTimeStep();	
	}

	if(disp < 0)
	{
		disp  = 0;
		vel = 0;
	}

	if(disp > stopHeight && stopHeight != 0)
	{
		disp = stopHeight;
		vel = 0;
	}
}

void Valve::calcDisDisp()
{
	if(disp == 0 && resultFor > 0 || disp > 0)
	{
		disp = disp + vel*simulPar.getTimeStep() + accel*pow(simulPar.getTimeStep(),2)/2;

		calcDisVel();

		calcDisAccel();

		cont++;
	}
}

void Valve::calcSucVel()
{
	vel += accel*simulPar.getTimeStep();
}

void Valve::calcDisVel()
{
	vel += accel*simulPar.getTimeStep();
}

void Valve::calcSucAccel()
{
	Constants cte;

	if(disp == 0 && resultFor > 0 || disp > 0)
	{	
		accel = resultFor/valveEquivMass -4*cte.Pi*valveDamp*valveNatFreq*vel - valveStiff/valveEquivMass*disp;
	
		calcSucVel();

		calcSucDisp();

	}
}

void Valve::calcDisAccel()
{
	Constants cte;

	if(disp < boostHeight)
	{
		accel = resultFor/valveEquivMass -4*cte.Pi*valveDamp*valveNatFreq*vel - valveStiff/valveEquivMass*disp;
	}
	else
	{
		accel = resultFor/equivMass -4*cte.Pi*valveDamp*natFreq*vel - stiff/equivMass*disp;
	}
	
	if(disp < 0)
	{
		disp  = 0;
		vel = 0;
	}

	if(disp > stopHeight && stopHeight != 0)
	{
		disp = stopHeight;
		vel = 0;
	}
}

void Valve::incremId()
{
	++id;
}

double Valve::getResultFor()
{
	return resultFor;
}

double Valve::getAccel()
{
	return  accel;
}

double Valve::getVel()
{
	return vel;
}

double Valve::getDisp()
{
	return disp;
}



