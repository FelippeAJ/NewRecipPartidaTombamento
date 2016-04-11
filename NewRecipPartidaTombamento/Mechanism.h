#ifndef MECHANISM_H
#define MECHANISM_H

#include <iostream>
#include <fstream>
#include <string>
#include "Constants.h"
#include "POLOIO.h"

class Mechanism
{
public:
	Mechanism();
	void calcSupDeadPt();
	void calcPos();
	void calcVel();
	void calcVelMed();
	void calcShaftVel();
	void incremTheta(double deltaTheta);

	double getSupDeadPt();
	double getPos();
	double getVel();
	double getVelMed();
	double getShaftVel();
	double getFreq();
	double getEccent();
	double getTheta();
	double getStroke();
	string getMech();
	
	Constants cte;

//protected:

	string mech;
	double supDeadPt;
	double stroke;
	double pos;
	double velMed;
	double rot;
	double shaftVel;
	double freq;
	double revers;
	double eccent;
	double rodLength;
	static double theta;
	static double vel;
	
};

#endif