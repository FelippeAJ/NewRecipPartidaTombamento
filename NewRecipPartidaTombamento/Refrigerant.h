#ifndef REFRIGERANT_H
#define REFRIGERANT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include "POLOIO.h"





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
	void setPress(double pressureValue);
	void setTemp(double temperatureValue);
	void setH(double enthalpyValue);
	void setCp(double cpValue);
	void setCv(double cvValue);
	void setVisc(double viscosityValue);
	void setThermConduc(double thermalConductivityValue);
	void setdPresDTemp(double dPresDTempValue);
	void setMass(double massValue);

	void calcMolWeight();
	void calcSatProp(long phaseFlag);
	void calcPress();
	void calcTempExplic(double derivTemp, double timeStep);
	void calcRho();
	void calcRho(double volVal);
	void calcMass(double volVal);
	void calcSpecHeat();
	void calcViscThermConduc();
	void calcDpresDtemp();
	void calcH();
	void calcS();
	void calcSpecHeatRat();
	void calcIsentProp();

	double getGasCt();
	double getMolWeight();
	double getPress();
	double getTemp();
	double getRho();
	double getRhoLiq();
	double getRhoVap();
	double getMass();
	double getCp();
	double getCv();
	double getVisc();
	double getThermConduc();
	double getDPresDTemp();
	double getH();
	double getS();
	double getSpeciHeatRat();

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
};

#endif

void setRefrigerant();

void loadRefprop();
