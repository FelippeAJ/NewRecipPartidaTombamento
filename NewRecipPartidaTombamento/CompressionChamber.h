#ifndef COMPRESSIONCHAMBER_H
#define COMPRESSIONCHAMBER_H

#include <iostream>
#include <string>
#include "Constants.h"
#include "Mechanism.h"
#include "Refrigerant.h"
#include "SuctionSystem.h"
#include "DischargeSystem.h"
#include "Oil.h"

using namespace std;

class CompressionChamber
{
public:
	CompressionChamber();

	void calcInicProp(Mechanism mech, double sucChambPress, double sucChambRho, double sucChambExpTemp); 
	void calcTemp(Mechanism mechObj, double sucChambH, double disChambH, SuctionSystem sucSystObj, DischargeSystem disSystObj, double timeStep, double leakMassFl);

	// Mechan
	void calcGapFricFact(double sucLinePres, double mechanVel);
	void calcContactLength();

	double getGapFricFact();
	
	//AdmNumber
	void calcRey(double rho, double vel, double caractLength, double visc);
	void calcPran(double visc,double cp, double thermConduct);
	void calcNus();

	//HeatTransfer
	void calcHeatTransfArea(double supDeadPoint, double mechPos);
	void calcConvCoef();

	//Cylinder
	void calcArea();
	void calcVol(double supDeadPt, double mechPos);
	void calcDispVol(double stroke);
	void calcDerivVol(double mechVel);
	void calcDerivTemp(double sucChambH, double disChambH, double sucFl, double sucfBackf, double disFl, double disBackf, double leakMassFl);
	void calcMassBal(double sucFl, double disFl, double leakFl, double timeStep);

	double getBore();
	double getLength();
	double getConLength();
	double getShaftDist();
	double getArea();
	double getVol();
	double getDispVol();
	double getDerivTemp();
	double getDeadVol();
	string getShape();


	//Piston
	void calcPistDiam();
	void calcDistBottPistTop(double mechanimPos);
	void calcDistBottPistPin();

	double getPistHeadLength();
	double getPistSkirtLength();
	double getDistBottPistPin();
	double getPistDiam();

	//Leak

	void calcLeakArea();
	void calcGapPistTop(double supDeadPt, double mechPos);
	void calcGapPistPin(double supDeadPt, double mechPos);
	void calcGapPistBott(double supDeadPt, double mechPos);
	void calcTopDiam();
	void calcBottDiam();

	double getGap();
	double getGapPistTop();
	double getGapPistPin();
	double getGapPistBott();
	double getTopDiam();
	double getBottDiam();
	double getLeakArea();
	double getTopArea();
	double getBottArea();

	Refrigerant refrig;
	Constants cte;
	Oil oilObj;

	double expTemp;

protected:


	//Mechanism
	double gapFricFact;
	double contLength;
	
	//AdmNumber
	static double Rey;
	static double Pran;
	static double Nus;

	//HeatTransfer
	static double heatTransfArea;
	static double convCoef;

	//Cylinder

	static string shape;
	double bore;
	double deadVol;
	double length;
	double conLength;
	double shaftDist;
	double vol;
	double dispVol;
	double derivTemp;
	static double derivVol;
	static double area;

	//Piston
	double pistSkirtLength;
	double pistHeadLength;
	static double pistDiam;
	double distBottPistTop;
	static double distBottPistPin;

	//Leak
	double gap;
	double gapInfDeadPt;
	double gapPistTop;
	double gapPistPin;
	double gapPistBott;
	double topDiam;
	double bottDiam;
	double leakArea;
	double topArea;
	double bottArea;

};

#endif;