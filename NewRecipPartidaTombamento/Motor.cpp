#include "Motor.h"

Motor::Motor()
{
	POLOIO POLOIOobj1("motor.dat");

	expTemp		=	POLOIOobj1.getParamVal("motor", "left") + 273.15;
	coefNum		=	POLOIOobj1.getParamVal("coeficient_number", "left");

	coeficients.resize(coefNum,0);

	string idStr;

	for(id = 0; id < coefNum; id++)
	{
		idStr = to_string(id);
		coeficients[id]	=	POLOIOobj1.getParamVal("coef", idStr, "left");
	}

	
	/**POLOIO POLOIOobj2("motor.dat");

	string idStr;
	int i;

	for(i=0; i < 5; i++)
	{
		idStr = to_string(i);
		coeficients[i]	=	POLOIOobj2.getParamVal("coef", idStr, "left");
	}*/
}

void Motor::setCoef(vector<double> coeficientsValue)
{
	for(int i = 0; i < coeficientsValue.size(); i++)
	{
		coeficients.push_back(coeficientsValue[i]);
	}
}

double Motor::getCoeficients(int id)
{
	return coeficients[id];
}

void Motor::calcEfficiency(double axisPotency)
{
	efficiency = interp.polynomialInterp(coeficients.size(), coeficients, axisPotency); 
}

void Motor::calcHeat(double consumption)
{
	heat = (1 - efficiency)*consumption;
}

double Motor::getEfficiency()
{
	return efficiency;
}

double Motor::getHeat()
{
	return heat;
}
