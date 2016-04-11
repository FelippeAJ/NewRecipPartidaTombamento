#include "Refrigerant.h"

fp_SETUPdllTYPE Refrigerant::SETUPdll = 0;
fp_WMOLdllTYPE  Refrigerant::WMOLdll = 0;
fp_SATTdllTYPE  Refrigerant::SATTdll = 0;
fp_TPRHOdllTYPE  Refrigerant::TPRHOdll = 0;
fp_TRNPRPdllTYPE  Refrigerant::TRNPRPdll = 0;
fp_DPDTdllTYPE  Refrigerant::DPDTdll = 0;
fp_CVCPdllTYPE  Refrigerant::CVCPdll = 0;
fp_ENTHALdllTYPE  Refrigerant::ENTHALdll = 0;
fp_ENTROdllTYPE  Refrigerant::ENTROdll = 0;
fp_PRESSdllTYPE  Refrigerant::PRESSdll = 0;
fp_PSFLSHdllTYPE Refrigerant::PSFLSHdll = 0;

char Refrigerant::herr[] = {"a"};

double Refrigerant::xcom[] = {0.0};

long Refrigerant::ierr = 0;

void loadRefprop()
{	
	HINSTANCE RefpropdllInstance;
	
	RefpropdllInstance = LoadLibrary(TEXT("refprop.DLL"));
	
	Refrigerant::SETUPdll = (fp_SETUPdllTYPE) GetProcAddress(RefpropdllInstance,"SETUPdll");
	Refrigerant::WMOLdll = (fp_WMOLdllTYPE) GetProcAddress(RefpropdllInstance,"WMOLdll");
	Refrigerant::SATTdll = (fp_SATTdllTYPE) GetProcAddress(RefpropdllInstance,"SATTdll");
	Refrigerant::TPRHOdll = (fp_TPRHOdllTYPE) GetProcAddress(RefpropdllInstance,"TPRHOdll");
	Refrigerant::TRNPRPdll = (fp_TRNPRPdllTYPE) GetProcAddress(RefpropdllInstance,"TRNPRPdll");
	Refrigerant::DPDTdll = (fp_DPDTdllTYPE) GetProcAddress(RefpropdllInstance,"DPDTdll");
	Refrigerant::CVCPdll = (fp_CVCPdllTYPE) GetProcAddress(RefpropdllInstance,"CVCPdll");
	Refrigerant::ENTHALdll = (fp_ENTHALdllTYPE) GetProcAddress(RefpropdllInstance,"ENTHALdll");
	Refrigerant::ENTROdll = (fp_ENTROdllTYPE) GetProcAddress(RefpropdllInstance,"ENTROdll");
	Refrigerant::PRESSdll = (fp_PRESSdllTYPE) GetProcAddress(RefpropdllInstance,"PRESSdll");
	Refrigerant::PSFLSHdll = (fp_PSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PSFLSHdll");
}

void setRefrigerant()
{	
	ifstream refrigerantReader;

	char refrigerantName[24];

	refrigerantReader.open("input.dat", ios::in);

	string tempName1;

	while(refrigerantReader >> tempName1)
	{
		if(tempName1 == "refrigerant")
		{
			refrigerantReader >> refrigerantName;
		}
	}


	const long refpropcharlength=255;
	const long lengthofreference=3;
	char hfmix[refpropcharlength+1];
	char hf[refpropcharlength*Refrigerant::ncmax];
	char hrf[lengthofreference+1];

	long icom; 

	char temp[255];
	char FluidName[24];

	if (FILE *FileMix = fopen(FluidName,"r"))
	{       
		fgets(temp,255,FileMix);

		fgets(temp,255,FileMix);
	
		fscanf(FileMix,"%d",&icom);

		for (int k = 0; k<icom; k++)
		{
			fscanf(FileMix,"%s",temp);

			if (k==0) 
			{
				strcpy(hf,temp);
			}

			else 
			{
				strcat(hf,temp);
			}

			if (k!=icom-1) 
			{
				strcat(hf,"|");
			}
		}
		strcpy(hfmix,"hmx.bnc");
		strcpy(hrf,"DEF");
		strcpy(Refrigerant::herr,"Ok");

		for(int k = 0; k<icom; k++)
		{
			fscanf(FileMix,"%lf",&Refrigerant::xcom[k]);
		}

		fclose(FileMix);
	}
	else
	{
		strcpy(FluidName,"fluids\\");
		strcat(FluidName,refrigerantName);
		strcat(FluidName,".FLD");

		
		if (FILE *FileFluid = fopen(FluidName,"r"))
		{
			fclose(FileFluid);

			icom=1;

			strcpy(hf,FluidName);

			strcpy(hfmix,"hmx.bnc");

			strcpy(hrf,"DEF");

			strcpy(Refrigerant::herr,"Ok");
		}
		else
		{
			printf("\nFluido refrigerante nao encontrado!\n");
			getchar();
			exit(1);
		}
	}

	Refrigerant::SETUPdll(icom, hf, hfmix, hrf, Refrigerant::ierr, Refrigerant::herr,refpropcharlength*Refrigerant::ncmax,refpropcharlength,lengthofreference,Refrigerant::errormessagelength);
}

Refrigerant::Refrigerant()
{
	calcMolWeight();
}

void Refrigerant::calcMolWeight()
{
	WMOLdll(xcom,molWeight);	
}

void Refrigerant::calcSatProp(long phaseFlag)
{
	double xliq[ncmax];
	double xvap[ncmax];

	SATTdll(temperature,xcom,phaseFlag,pressure,rhoLiquid,rhoVapor,xliq,xvap,ierr,herr,errormessagelength);

	pressure = pressure*1.e+3;

	rhoLiquid = rhoLiquid*molWeight;

	rhoVapor = rhoVapor*molWeight;
}

void Refrigerant::calcPress()
{
	rho = rho/molWeight;

	PRESSdll(temperature,rho,xcom,pressure);

	pressure = pressure*1.e+3;

	rho = rho*molWeight;
}

void Refrigerant::calcTempExplic(double derivTemp, double timeStep)
{
	temperature += derivTemp*timeStep;
}

void Refrigerant::calcRho()
{
	long kph = 2;
	long kguess = 0;
	long aux = 0;
	
	pressure = pressure/1.e3;													// [kPa]
	
	TPRHOdll (temperature,pressure,xcom,kph,kguess,rho,ierr,herr,aux);

	rho = rho*molWeight;

	pressure = pressure*1.e3;
}

void Refrigerant::calcRho(double volVal)
{
	rho = mass/volVal;
}

void Refrigerant::calcMass(double volVal)
{
	mass = rho*volVal;
}

void Refrigerant::calcSpecHeat()
{
	rho = rho/molWeight;

	CVCPdll (temperature,rho,xcom,cv,cp);

	cv =  cv/molWeight*1000.0;

	cp =  cp/molWeight*1000.0;	

	rho = rho*molWeight;
}

void Refrigerant::calcViscThermConduc()
{	
	long aux = 0;

	rho = rho/molWeight;

	TRNPRPdll (temperature,rho,xcom,viscosity,thermalConductivity,ierr,herr,aux);

	viscosity = viscosity*1.0e-6;

	rho = rho*molWeight;
}

void Refrigerant::calcDpresDtemp()
{
	rho = rho/molWeight;

	DPDTdll (temperature,rho,xcom,dPresDTemp);

	dPresDTemp = dPresDTemp*1.e+3;

	rho = rho*molWeight;
}

void Refrigerant::calcH()
{
	rho = rho/molWeight;

	ENTHALdll(temperature,rho,xcom,enthalpy);
	
	enthalpy = enthalpy/molWeight*1000.0;

	rho = rho*molWeight;
}

void Refrigerant::calcS()
{
	rho = rho/molWeight;

	ENTROdll(temperature,rho,xcom,entropy);
	
	entropy = entropy/molWeight*1000.0;

	rho = rho*molWeight;
}

void Refrigerant::calcSpecHeatRat()
{
	specificHeatsRatio = cp/cv;
}

void Refrigerant::calcIsentProp()
{
	long aux = 0;

	double x[3];
	double y[3];
	double q;
	double e;
	double w;
	double dl;
	double dv;

	entropy = entropy*molWeight/1000;

	pressure = pressure/1.0e3;

	PSFLSHdll (pressure,entropy,xcom,temperature,rho,dl,dv,x,y,q,e,enthalpy,cv,cp,w,ierr,herr,aux);

	entropy = entropy*molWeight/1000;

	enthalpy = enthalpy/molWeight*1000.0;
}

void Refrigerant::setPress(double pressureVal)
{
	pressure = pressureVal;
}

void Refrigerant::setTemp(double temperatureVal)
{
	temperature = temperatureVal;
}

void Refrigerant::setH(double enthalpyVal)
{
	enthalpy = enthalpyVal;
}

void Refrigerant::setCp(double cpVal)
{
	cp = cpVal;
}

void Refrigerant::setCv(double cvVal)
{
	cv = cvVal;
}

void Refrigerant::setVisc(double viscosityVal)
{
	viscosity = viscosityVal;
}

void Refrigerant::setThermConduc(double thermalConductivityVal)
{
	thermalConductivity = thermalConductivityVal;
}

void Refrigerant::setdPresDTemp(double dPresDTempVal)
{
	dPresDTemp = dPresDTempVal;
}

void Refrigerant::setMass(double massVal)
{
	mass = massVal;
}

void Refrigerant::setRho(double rhoVal)
{
	rho = rhoVal;
}

double Refrigerant::getMolWeight()
{
	return molWeight;
}

double Refrigerant::getGasCt()
{
	return 8314.5/molWeight;
}

double Refrigerant::getPress()
{
	return pressure;
}

double Refrigerant::getTemp()
{
	return temperature;
}

double Refrigerant::getRho()
{
	return rho;
}

double Refrigerant::getRhoLiq()
{
	return rhoLiquid;
}

double Refrigerant::getRhoVap()
{
	return rhoVapor;
}

double Refrigerant::getMass()
{
	return mass;
}

double Refrigerant::getCp()
{
	return cp;
}

double Refrigerant::getCv()
{
	return cv;
}

double Refrigerant::getVisc()
{
	return viscosity;
}

double Refrigerant::getThermConduc()
{
	return thermalConductivity;
}

double Refrigerant::getDPresDTemp()
{
	return dPresDTemp;
}

double Refrigerant:: getH()
{
	return enthalpy;
}

double Refrigerant::getS()
{
	return entropy;
}

double Refrigerant::getSpeciHeatRat()
{
	return specificHeatsRatio;
}


