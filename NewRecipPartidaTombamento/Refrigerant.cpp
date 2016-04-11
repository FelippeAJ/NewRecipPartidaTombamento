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

int Refrigerant::id = 1;

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

void setRefrigerant(char refrigerantName[])
{	
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
	Input refrigerantReader;

	refrigerantReader.readRefrigerantData();

	Input reader;
	reader.readRefrigerantData();

	calcMolWeight();
}

void Refrigerant::calcMolWeight()
{
	WMOLdll(xcom,molWeight);	
}

void Refrigerant::calcSaturationProperties(long phaseFlagValue)
{
	double xliq[ncmax];
	double xvap[ncmax];

	SATTdll(temperature,xcom,phaseFlagValue,pressure,rhoLiquid,rhoVapor,xliq,xvap,ierr,herr,errormessagelength);

	pressure = pressure*1.e+3;

	rhoLiquid = rhoLiquid*molWeight;

	rhoVapor = rhoVapor*molWeight;
}

void Refrigerant::calcPressure()
{
	rho = rho/molWeight;

	PRESSdll(temperature,rho,xcom,pressure);

	pressure = pressure*1.e+3;

	rho = rho*molWeight;
}

void Refrigerant::calcTemperatureExplicitily(double derivateTemperature, double timeStep)
{
	temperature += derivateTemperature*timeStep;
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

void Refrigerant::calcRho(double volumeValue)
{
	rho = mass/volumeValue;
}

void Refrigerant::calcMass(double volumeValue)
{
	mass = rho*volumeValue;
}

void Refrigerant::calcSpecificHeats()
{
	rho = rho/molWeight;

	CVCPdll (temperature,rho,xcom,cv,cp);

	cv =  cv/molWeight*1000.0;

	cp =  cp/molWeight*1000.0;	

	rho = rho*molWeight;
}

void Refrigerant::calcViscosityThermalConductivity(double thetaValue)
{	
	long aux = 0;

	rho = rho/molWeight;

	//if(viscosityThermalCond == "refprop" || (thetaValue - 2*cte.Pi) < 1E-11)	
	//{
		TRNPRPdll (temperature,rho,xcom,viscosity,thermalConductivity,ierr,herr,aux);

		viscosity = viscosity*1.0e-6;
	//}
	/*else
	if(viscosityThermalCond == "interp" && (thetaValue -  2*cte.Pi) > 1E-11)
	{
		Spline_interp static viscosityObj(tabledTemperature,tabledViscosity);

		Spline_interp static thermalCondObj(tabledTemperature,tabledThermalConductivity);

		viscosity = viscosityObj.interp(temperature);
		
		thermalConductivity = thermalCondObj.interp(temperature); 	
	}*/

	rho = rho*molWeight;
}

void Refrigerant::calcDpresDtemp()
{
	rho = rho/molWeight;

	DPDTdll (temperature,rho,xcom,dPresDTemp);

	dPresDTemp = dPresDTemp*1.e+3;

	rho = rho*molWeight;
}

void Refrigerant::calcEntalphy()
{
	rho = rho/molWeight;

	ENTHALdll(temperature,rho,xcom,enthalpy);
	
	enthalpy = enthalpy/molWeight*1000.0;

	rho = rho*molWeight;
}

void Refrigerant::calcEntropy()
{
	rho = rho/molWeight;

	ENTROdll(temperature,rho,xcom,entropy);
	
	entropy = entropy/molWeight*1000.0;

	rho = rho*molWeight;
}

void Refrigerant::calcSpecificHeatsRatio()
{
	specificHeatsRatio = cp/cv;
}

void Refrigerant::calcIsentropicProperties()
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

void Refrigerant::setPressure(double pressureValue)
{
	pressure = pressureValue;
}

void Refrigerant::setTemperature(double temperatureValue)
{
	temperature = temperatureValue;
}

void Refrigerant::setMass(double massValue)
{
	mass = massValue;
}

void Refrigerant::setViscosityThermalCond(string viscosityThermalCondName)
{
	viscosityThermalCond = viscosityThermalCondName;
}

void Refrigerant::dimensionTabledProperties(double deltaTheta)
{
	tabledViscosity.resize((int)(ceil(2.0*cte.Pi/deltaTheta))+2);

	tabledThermalConductivity.resize((int)(ceil(2.*cte.Pi/deltaTheta))+2);
	
	tabledTemperature.resize((int)(ceil(2.0*cte.Pi/deltaTheta))+2);
}

void Refrigerant::setTabledProperties(double deltaTheta)
{	
	tabledTemperature[id] = temperature;

	tabledViscosity[id] = viscosity;

	tabledThermalConductivity[id] = thermalConductivity;

	if(id  == ceil(2.*cte.Pi/deltaTheta))
	{
		tabledTemperature[0] =  5;

		tabledViscosity[0] = 1.1E-5;

		tabledThermalConductivity[0] = 0.012;

		tabledTemperature[tabledTemperature.size()-1] = 480;

		tabledViscosity[tabledViscosity.size()-1] = 2.4E-5;

		tabledThermalConductivity[tabledThermalConductivity.size()-1] = 0.035;
	}	

	++id;
}

void Refrigerant::setRho(double rhoValue)
{
	rho = rhoValue;
}

double Refrigerant::getMolWeight()
{
	return molWeight;
}

double Refrigerant::getGasConstant()
{
	return 8314.5/molWeight;
}

double Refrigerant::getPressure()
{
	return pressure;
}

double Refrigerant::getTemperature()
{
	return temperature;
}

double Refrigerant::getRho()
{
	return rho;
}

double Refrigerant::getRhoLiquid()
{
	return rhoLiquid;
}

double Refrigerant::getRhoVapor()
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

double Refrigerant::getViscosity()
{
	return viscosity;
}

double Refrigerant::getThermalConductivity()
{
	return thermalConductivity;
}

double Refrigerant::getDPresDTemp()
{
	return dPresDTemp;
}

double Refrigerant:: getEnthalpy()
{
	return enthalpy;
}

double Refrigerant::getEntropy()
{
	return entropy;
}

double Refrigerant::getSpecificHeatsRatio()
{
	return specificHeatsRatio;
}



/*


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

char Refrigerant::herr[] = {"a"};

double Refrigerant::xcom[] = {0.0};

long Refrigerant::ierr = 0;

int Refrigerant::id = 1;

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
}

void setRefrigerant(char refrigerantName[])
{	
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
	Input refrigerantReader;

	refrigerantReader.readRefrigerantData();

	setViscosityThermalCond(refrigerantReader.getRefrigViscThermalCondCalc());

	calcMolWeight();
}

void Refrigerant::calcMolWeight()
{
	WMOLdll(xcom,molWeight);	
}

void Refrigerant::calcSaturationProperties(long phaseFlagValue)
{
	double xliq[ncmax];
	double xvap[ncmax];

	SATTdll(temperature,xcom,phaseFlagValue,pressure,rhoLiquid,rhoVapor,xliq,xvap,ierr,herr,errormessagelength);

	pressure = pressure*1.e+3;

	rhoLiquid = rhoLiquid*molWeight;

	rhoVapor = rhoVapor*molWeight;
}

void Refrigerant::calcPressure()
{
	rho = rho/molWeight;

	PRESSdll(temperature,rho,xcom,pressure);

	pressure = pressure*1.e+3;
}

void Refrigerant::calcTemperatureExplicitily(double derivateTemperature, double timeStep)
{
	temperature += derivateTemperature*timeStep;
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

void Refrigerant::calcRho(double volumeValue)
{
	rho = mass/volumeValue;
}

void Refrigerant::calcMass(double volumeValue)
{
	mass = rho*volumeValue;
}

void Refrigerant::calcSpecificHeats()
{
	rho = rho/molWeight;

	CVCPdll (temperature,rho,xcom,cv,cp);

	cv =  cv/molWeight*1000.0;

	cp =  cp/molWeight*1000.0;	

	rho = rho*molWeight;
}

void Refrigerant::calcViscosityThermalConductivity(double thetaValue)
{	
	long aux = 0;

	rho = rho/molWeight;

	double tempValue = 6.28;

	if( (abs(thetaValue - tempValue)) < 1E-11)
	{	
		TRNPRPdll (*min_element(tempTemperature.begin(),tempTemperature.end()),*min_element(tempRho.begin(),tempRho.end()),xcom,viscosity,thermalConductivity,ierr,herr,aux);
		
		equivViscostyMin  = viscosity*1.0e-6;;
		
		equivThermalConductivityMin = thermalConductivity;

		equivTemperatureMin = *min_element(tempTemperature.begin(),tempTemperature.end());

		TRNPRPdll (*max_element(tempTemperature.begin(),tempTemperature.end()),*max_element(tempRho.begin(),tempRho.end()),xcom,viscosity,thermalConductivity,ierr,herr,aux);
	
		equivViscostyMax = viscosity*1.0e-6;
	
		equivThermalConductivityMax = thermalConductivity;

		equivTemperatureMax = *max_element(tempTemperature.begin(),tempTemperature.end());
	}



	if(viscosityThermalCond == "refprop" || (thetaValue - tempValue) < 1E-11)	
	{
		TRNPRPdll (temperature,rho,xcom,viscosity,thermalConductivity,ierr,herr,aux);

		viscosity = viscosity*1.0e-6;

		rho = rho*molWeight;

		tempTemperature.push_back(temperature);

		tempRho.push_back(rho);
	}
	else
	if(viscosityThermalCond == "interp" && (thetaValue - tempValue) > 1E-11)
	{
		Linear_interp static viscosityObj(tabledTemperature,tabledViscosity);

		Linear_interp static thermalCondObj(tabledTemperature,tabledThermalConductivity);

		viscosity = viscosityObj.interp(temperature);
		
		thermalConductivity = thermalCondObj.interp(temperature); 	
	}

	//rho = rho*molWeight;
}

void Refrigerant::calcDpresDtemp()
{
	rho = rho/molWeight;

	DPDTdll (temperature,rho,xcom,dPresDTemp);

	dPresDTemp = dPresDTemp*1.e+3;

	rho = rho*molWeight;
}

void Refrigerant::calcEntalphy()
{
	rho = rho/molWeight;

	ENTHALdll(temperature,rho,xcom,enthalpy);
	
	enthalpy = enthalpy/molWeight*1000.0;

	rho = rho*molWeight;
}

void Refrigerant::calcEntropy()
{
	rho = rho/molWeight;

	ENTROdll(temperature,rho,xcom,entropy);
	
	entropy = entropy/molWeight*1000.0;

	rho = rho*molWeight;
}

void Refrigerant::calcSpecificHeatsRatio()
{
	specificHeatsRatio = cp/cv;
}

void Refrigerant::setPressure(double pressureValue)
{
	pressure = pressureValue;
}

void Refrigerant::setTemperature(double temperatureValue)
{
	temperature = temperatureValue;
}

void Refrigerant::setMass(double massValue)
{
	mass = massValue;
}

void Refrigerant::setViscosityThermalCond(string viscosityThermalCondName)
{
	viscosityThermalCond = viscosityThermalCondName;
}

void Refrigerant::setTabledProperties(double thetaValue)
{
		double tempValue = 6.28;
	
		tabledTemperature[id] = temperature;

		tabledViscosity[id] = viscosity;

		tabledThermalConductivity[id] = thermalConductivity;

		if( (abs(thetaValue - tempValue)) < 1E-11)	
		{
			tabledTemperature[0] = equivTemperatureMin - 50;

			tabledViscosity[0] = equivViscostyMin;

			tabledThermalConductivity[0] = equivThermalConductivityMin;

			tabledTemperature[tabledTemperature.size() -1] = equivTemperatureMax + 50;

			tabledViscosity[tabledViscosity.size() -1] = equivViscostyMax;

			tabledThermalConductivity[tabledThermalConductivity.size() -1 ] = equivThermalConductivityMax;
		}	

		++id;
}

void Refrigerant::dimensionTabledProperties(double cyclesNumber, double deltaTheta)
{
	tabledViscosity.resize((int)(ceil(2.0*cte.Pi/deltaTheta))+2);

	tabledThermalConductivity.resize((int)(ceil(2.*cte.Pi/deltaTheta))+2);
	
	tabledTemperature.resize((int)(ceil(2.0*cte.Pi/deltaTheta))+2);
}

void Refrigerant::setRho(double rhoValue)
{
	rho = rhoValue;
}

double Refrigerant::getMolWeight()
{
	return molWeight;
}

double Refrigerant::getGasConstant()
{
	return 8314.5/molWeight;
}

double Refrigerant::getPressure()
{
	return pressure;
}

double Refrigerant::getTemperature()
{
	return temperature;
}

double Refrigerant::getRho()
{
	return rho;
}

double Refrigerant::getRhoLiquid()
{
	return rhoLiquid;
}

double Refrigerant::getRhoVapor()
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

double Refrigerant::getViscosity()
{
	return viscosity;
}

double Refrigerant::getThermalConductivity()
{
	return thermalConductivity;
}

double Refrigerant::getDPresDTemp()
{
	return dPresDTemp;
}

double Refrigerant:: getEnthalpy()
{
	return enthalpy;
}

double Refrigerant::getEntropy()
{
	return entropy;
}

double Refrigerant::getSpecificHeatsRatio()
{
	return specificHeatsRatio;
}







*/