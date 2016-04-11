#ifndef LEAK_H
#define LEAK_H

#include "POLOIO.h"
#include "Constants.h"
#include "Refrigerant.h"
#include "CompressionChamber.h"

class Leak
{
public:
	Leak();


	void calcVel(CompressionChamber compChambObj, double sucLinePress, double visc, double mechVel);
	void calcMassFl(double oldRhoValue, CompressionChamber compChambObj);
	void calcMassSum(double timeStep);

	double getMassFl();
	double getMassSumFl();
	double getMassSumBackf();
	
	Refrigerant refrig;
	Constants cte;

protected:
	
	double shellPress;
	string seal;
	double vel;
	double topVel;
	double bottVel;
	double massFl;
	double topMassFl;
	double bottMassFl;
	double massSumFl;
	double massSumBackf;
};

#endif











