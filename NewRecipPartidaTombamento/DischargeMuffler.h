#ifndef DISCHARGEMUFFLER_H
#define DISCHARGEMUFFLER_H

#include <iostream>
#include <string>
#include <cmath>
#include "Refrigerant.h"
#include "POLOIO.h"
#include "Constants.h"


class DischargeMuffler
{
public:

	DischargeMuffler();			

	void simul(double massFl, double disChambPress, double disChambTemp, double compChambTemp, double extTemp, double disLinePress, double disLineTemp);		
	void readGeomDat();												
	void boundCond(double disLinePress, double disLineTemp, double extTemp);			
	void calcVel( double massFl);
	void calcPress(double massFl);
	void calcTemp(double massFl, double compChambTemp);
	vector<double> TDMA(int ISTART,int IEND, vector<double> ae, vector<double> aw, vector<double> ap, vector<double> su, vector<double> PHI);
	void inicVect(double disChambTemp, double disLineTemp);						
	void dimenVec();
	void calcDt(double deltaTheta, double shaftVel);

	Refrigerant refrig;
	Constants cte;
	
	int cont;
	int volNum,chambNum;
	double T1d;
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

	double  expTemp;

	double dt;

};

#endif