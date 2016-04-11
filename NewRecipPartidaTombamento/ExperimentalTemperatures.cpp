#include "ExperimentalTemperatures.h"

ExperimentalTemperatures::ExperimentalTemperatures()
{
	Input expTempReaderData;

	expTempReaderData.readExpTempData();

	setEvaporationTemp(expTempReaderData.getExpTempEvaporation() );
	setCondesationTemp(expTempReaderData.getExpTempCondesation());
	setSubcoolingTemp(expTempReaderData.getExpTempSubcooling());
	setSuperheatingTemp(expTempReaderData.getExpTempSuperheating());
	setSucLineTemp(expTempReaderData.getExpTempSuctionLine());
	setDisLineTemp(expTempReaderData.getExpTempDischargeLine());
	setSucChamberTemp(expTempReaderData.getExpTempSuctionChamber());
	setDisChamberTemp(expTempReaderData.getExpTempDischargeChamber());
	setCylinderWallTemp(expTempReaderData.getExpTempCylinderWall());
	setBearingsTemp(expTempReaderData.getExpTempBearings());
	setOilTemp(expTempReaderData.getExpTempOil());
	setMotorTemp(expTempReaderData.getExpTempMotor());
	setInternalEnvironment(expTempReaderData.getExpTempInternalEnvironment()); 
	setExternalEnvironment(expTempReaderData.getExpTempExternalEnvironment()); 
	setDischargeMuffler(expTempReaderData.getExpTempDischargeMuffler()); 
	setShell(expTempReaderData.getExpTempShell()); 
}

void ExperimentalTemperatures::setEvaporationTemp(double evaporationTempValue)
{
	evaporationTemp = evaporationTempValue;
}

void ExperimentalTemperatures::setCondesationTemp(double condesationTempValue)
{
	condesationTemp = condesationTempValue;
}

void ExperimentalTemperatures::setSubcoolingTemp(double subcoolingTempValue)
{
	subcoolingTemp = subcoolingTempValue;
}

void ExperimentalTemperatures::setSuperheatingTemp(double superheatingTempValue)
{
	superheatingTemp = superheatingTempValue;
}

void ExperimentalTemperatures::setSucLineTemp(double suctionLineTempValue)
{
	suctionLineTemp = suctionLineTempValue;
}

void ExperimentalTemperatures::setDisLineTemp(double dischargeLineTempValue)
{
	dischargeLineTemp = dischargeLineTempValue;
}

void ExperimentalTemperatures::setSucChamberTemp(double suctionChamberTempValue)
{
	suctionChamberTemp = suctionChamberTempValue;
}

void ExperimentalTemperatures::setDisChamberTemp(double dischargeChamberTempValue)
{
	dischargeChamberTemp = dischargeChamberTempValue;
}

void ExperimentalTemperatures::setCylinderWallTemp(double cylinderWallTempValue)
{
	cylinderWallTemp = cylinderWallTempValue;
}

void ExperimentalTemperatures::setBearingsTemp(double bearingsTempValue)
{
	bearingsTemp = bearingsTempValue;
}

void ExperimentalTemperatures::setOilTemp(double oilTempValue)
{
	oilTemp = oilTempValue;
}

void ExperimentalTemperatures::setMotorTemp(double motorTempValue)
{
	motorTemp = motorTempValue;
}

void ExperimentalTemperatures::setDischargeMuffler(double dischargeMufflerValue)
{
	dischargeMuffler = dischargeMufflerValue;
}

void ExperimentalTemperatures::setExternalEnvironment(double externalEnvironmentValue)
{
	externalEnvironment = externalEnvironmentValue;
}

void ExperimentalTemperatures::setInternalEnvironment(double internalEnvironmentValue)
{
	internalEnvironment = internalEnvironmentValue;
}

void ExperimentalTemperatures::setShell(double shellValue)
{
	shell = shellValue;
}

double ExperimentalTemperatures::getInternalEnvironment()
{
	return internalEnvironment;
}

double ExperimentalTemperatures::getExternalEnvironment()
{
	return externalEnvironment;
}

double ExperimentalTemperatures::getDischargeMuffler()
{
	return dischargeMuffler;
}

double ExperimentalTemperatures::getShell()
{
	return shell;
}

double ExperimentalTemperatures::getEvaporationTemp()
{
	return evaporationTemp;
}

double ExperimentalTemperatures::getCondesationTemp()
{
	return condesationTemp;
}

double ExperimentalTemperatures::getSubcoolingTemp()
{
	return subcoolingTemp;
}

double ExperimentalTemperatures::getSuperheatingTemp()
{
	return superheatingTemp;
}

double ExperimentalTemperatures::getSucLineTemp()
{
	return suctionLineTemp;
}

double ExperimentalTemperatures::getDisLineTemp()
{
	return dischargeLineTemp;
}

double ExperimentalTemperatures::getSucChamberTemp()
{
	return suctionChamberTemp;
}

double ExperimentalTemperatures::getDisChamberTemp()
{
	return dischargeChamberTemp;
}

double ExperimentalTemperatures::getCylinderWallTemp()
{
	return cylinderWallTemp;
}

double ExperimentalTemperatures::getBearingsTemp()
{
	return bearingsTemp;
}

double ExperimentalTemperatures::getOilTemp()
{
	return oilTemp;
}

double ExperimentalTemperatures::getMotorTemp()
{
	return motorTemp;
}