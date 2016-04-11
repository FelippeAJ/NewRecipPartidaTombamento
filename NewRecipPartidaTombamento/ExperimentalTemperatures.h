#ifndef EXPERIMENTALTEMPERATURES_H
#define EXPERIMENTALTEMPERATURES_H

#include "Input.h"

class ExperimentalTemperatures
{
public:
	ExperimentalTemperatures();

	void setEvaporationTemp(double evaporationTempValue);
	void setCondesationTemp(double condesationTempValue);
	void setSubcoolingTemp(double subcoolingTempValue);
	void setSuperheatingTemp(double superheatingTempValue);
	void setSucLineTemp(double suctionLineTempValue);
	void setDisLineTemp(double dischargeLineTempValue);
	void setSucChamberTemp(double suctionChamberTempValue);
	void setDisChamberTemp(double dischargeChamberTempValue);
	void setCylinderWallTemp(double cylinderWallTempValue);
	void setBearingsTemp(double bearingsTempValue);
	void setOilTemp(double oilTempValue);
	void setMotorTemp(double motorTempValue);
	void setInternalEnvironment(double internalEnvironmentValue);
	void setDischargeMuffler(double dischargeMufflerValue);
	void setShell(double shellValue);
	void setExternalEnvironment(double externalEnvironmentValue);

	double getEvaporationTemp();
	double getCondesationTemp();
	double getSubcoolingTemp();
	double getSuperheatingTemp();
	double getSucLineTemp();
	double getDisLineTemp();
	double getSucChamberTemp();
	double getDisChamberTemp();
	double getCylinderWallTemp();
	double getBearingsTemp();
	double getOilTemp();
	double getMotorTemp();
	double getInternalEnvironment();
	double getDischargeMuffler();
	double getShell();
	double getExternalEnvironment();

protected:
	double evaporationTemp;
	double condesationTemp;
	double subcoolingTemp;
	double superheatingTemp;
	double suctionLineTemp;
	double dischargeLineTemp;
	double suctionChamberTemp;
	double dischargeChamberTemp;
	double cylinderWallTemp;
	double bearingsTemp;
	double oilTemp;
	double motorTemp;
	double internalEnvironment;
	double dischargeMuffler;
	double shell;
	double externalEnvironment;
};

#endif