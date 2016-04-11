#ifndef SUCTIONMUFFLER_H
#define SUCTIONMUFFLER_H

#include <iostream>
#include <string>
#include <cmath>
#include "POLOIO.h"
#include "Refrigerant.h"
#include "Constants.h"

using namespace std;

class SuctionMuffler
{
public:
	SuctionMuffler();
	void simul(double massFl, double sucChambPress, double sucChambTemp, double compChambTemp, double extTemp, double sucLinePress);
	void readGeomDat();
	void boundCond(double sucLinePress, double extTemp, double compChambTemp);
	void calcVel( double massFl);
	void calcPress(double massFl);
	void calcTemp(double massFl, double compChambTemp);
	vector<double> TDMA(int ISTART,int IEND, vector<double> ae, vector<double> aw, vector<double> ap, vector<double> su, vector<double> PHI);
	void inicVect(double sucChambTemp);
	void dimenVec();
	void calcDt(double deltaTheta, double shaftVel);

	Refrigerant refrig;
	Constants cte;
	
	int cont;
    int volNum,chambNum;
	vector<double>  u,u0,d,ccp,p,p0,T,ro;

protected:

	double pressConvergCrit,massConvergCrit,tempConvergCrit,pressRelaxCoef,velRelaxCoef,tempRelaxCoef,visc,R,cp,kt,entTemp,extTemp,zeroFlFricFact;
	vector<int>  chambId;
	vector<int>  tubeVolNum;
	vector<double>  T0,Taux,ro0,dx,DTp;
	vector<double>  Du,ATp,Au;

	double massResid;
	vector<double> rou, rou0;
	vector<double> Fe, Fw, f;
	vector<double> apu, aeu, awu, spu, suu;
	vector<double> Re;

	double pressResid;
	vector<double> app, aep, awp, sup;
	vector<double> roe, row;
	vector<double> mrop, mroe, mrow, mue, muw;

	vector<double> apT, aeT, awT, suT;
	double tempResid;

	double expTemp;

	double dt;



};

#endif