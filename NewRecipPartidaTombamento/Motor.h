#ifndef MOTOR_H
#define MOTOR_H

#include "POLOIO.h"
#include "Interpolation.h"

class Motor
{
public:
	Motor();
	void calcEfficiency(double axisPotency);
	void calcHeat(double consumption);
	void setCoef(vector<double> coeficientsValue);
	
	double getCoeficients(int id);
	double getEfficiency(); 
	double getHeat();

	double expTemp;


protected:
	vector<double> coeficients;
	double efficiency;
	double heat;
	Interpolation interp;
	int coefNum;
	int id;
};

#endif

