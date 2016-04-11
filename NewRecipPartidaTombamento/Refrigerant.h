#ifndef REFRIGERANT_H
#define REFRIGERANT_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "Input.h"
#include "Constants.h"
#include "NumericalRecipes.h"


#include "Crank.h"

using namespace std;

typedef void (__stdcall *fp_SETUPdllTYPE)(long &,char*,char*,char*,long &,char*,long ,long ,long ,long );
typedef void (__stdcall *fp_WMOLdllTYPE)(double *,double &);
typedef void (__stdcall *fp_SATTdllTYPE)(double &,double *,long &,double &,double &,double &,double *,double *,long &,char*,long );
typedef void (__stdcall *fp_TPRHOdllTYPE)(double &,double &,double *,long &,long &,double &,long &,char*,long );
typedef void (__stdcall *fp_TRNPRPdllTYPE)(double &,double &,double *,double &,double &,long &,char*,long );
typedef void (__stdcall *fp_DPDTdllTYPE)(double &,double &,double *,double &);
typedef void (__stdcall *fp_CVCPdllTYPE)(double &,double &,double *,double &,double &);
typedef void (__stdcall *fp_ENTHALdllTYPE)(double &,double &,double *,double &);
typedef void (__stdcall *fp_ENTROdllTYPE)(double &,double &,double *,double &);
typedef void (__stdcall *fp_PRESSdllTYPE)(double &,double &,double *,double &);
typedef void (__stdcall *fp_PSFLSHdllTYPE)(double &,double &,double *,double &,double &,double &,double &,double *,double *,double &,double &,double &,double &,double &,double &,long &,char*,long );

class Refrigerant
{
public:
	Refrigerant();

	void setRho(double rhoValue);
	void setPressure(double pressureValue);
	void setTemperature(double temperatureValue);
	void setMass(double massValue);
	void setViscosityThermalCond(string viscosityThermalCondName);
	void dimensionTabledProperties(double deltaTheta);
	void setTabledProperties(double deltaTheta);

	void calcMolWeight();
	void calcSaturationProperties(long phaseFlagValue);
	void calcPressure();
	void calcTemperatureExplicitily(double derivateTemperature, double timeStep);
	void calcRho();
	void calcRho(double volumeValue);
	void calcMass(double volumeValue);
	void calcSpecificHeats();
	void calcViscosityThermalConductivity(double thetaValue);
	void calcDpresDtemp();
	void calcEntalphy();
	void calcEntropy();
	void calcSpecificHeatsRatio();
	void calcIsentropicProperties();

	double getGasConstant();
	double getMolWeight();
	double getPressure();
	double getTemperature();
	double getRho();
	double getRhoLiquid();
	double getRhoVapor();
	double getMass();
	double getCp();
	double getCv();
	double getViscosity();
	double getThermalConductivity();
	double getDPresDTemp();
	double getEnthalpy();
	double getEntropy();
	double getSpecificHeatsRatio();

	static fp_SETUPdllTYPE SETUPdll;
	static fp_WMOLdllTYPE WMOLdll;
	static fp_SATTdllTYPE SATTdll;
	static fp_TPRHOdllTYPE TPRHOdll;
	static fp_TRNPRPdllTYPE TRNPRPdll;
	static fp_DPDTdllTYPE DPDTdll;
	static fp_CVCPdllTYPE CVCPdll;
	static fp_ENTHALdllTYPE ENTHALdll;
	static fp_ENTROdllTYPE ENTROdll;
	static fp_PRESSdllTYPE PRESSdll;
	static fp_PSFLSHdllTYPE PSFLSHdll;

	Constants cte;

	static const long ncmax = 20;
	static const long errormessagelength=255;
	static char herr[errormessagelength+1];
	static double xcom[ncmax];
	static long ierr;

protected:
	double molWeight;
	double gasConstant;
	double temperature;
	double pressure;
	double rho;
	double rhoLiquid;
	double rhoVapor;
	double mass;
	double cp;
	double cv;
	double enthalpy;
	double entropy;
	double viscosity;
	double thermalConductivity;
	double dPresDTemp;
	double specificHeatsRatio;

	string viscosityThermalCond;
	VecDoub tabledViscosity;
	VecDoub tabledThermalConductivity;
	VecDoub tabledTemperature;
	static int id;
};

#endif

void setRefrigerant(char refrigerantName[]);

void loadRefprop();
