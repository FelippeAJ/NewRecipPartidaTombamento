#include "ThermalBalance.h"

ThermalBalance::ThermalBalance()
{
}

void ThermalBalance::calcThermalBalance(Compressor compressorObj)
{	
	ofstream exportData;
	exportData.open("NewRecip_UAs.dat", ios::out);

	compressorObj.motor.UAobj.calcUA(compressorObj.expTemp.getMotorTemp(), compressorObj.expTemp.getInternalEnvironment());
	compressorObj.motor.heatTransferRateObj.calcHeatTransferRate(compressorObj.motor.UAobj.getUA(), compressorObj.expTemp.getMotorTemp(), compressorObj.expTemp.getInternalEnvironment());
	exportData << "UA Motor-InternalEnvironment\t" << compressorObj.motor.UAobj.getUA() << endl;

	compressorObj.compressionChamberObj.cyl.UAobj.calcUA(compressorObj.expTemp.getCylinderWallTemp(), compressorObj.expTemp.getInternalEnvironment());
	compressorObj.compressionChamberObj.cyl.heatTransferRateObj.calcHeatTransferRate(compressorObj.compressionChamberObj.cyl.UAobj.getUA(), compressorObj.expTemp.getCylinderWallTemp(), compressorObj.expTemp.getInternalEnvironment());
	exportData << "UA Cylinder-InternalEnvironment\t" << compressorObj.compressionChamberObj.cyl.UAobj.getUA() << endl;

	compressorObj.sucMuffler.calcSuctionMufflerAverageTemp(compressorObj.expTemp.getSucLineTemp(), compressorObj.expTemp.getSucChamberTemp());
	compressorObj.sucMuffler.UAobj.calcUA(compressorObj.sucMuffler.getSuctionMufflerAverageTemp(), compressorObj.expTemp.getInternalEnvironment());
	compressorObj.sucMuffler.heatTransferRateObj.calcHeatTransferRate(compressorObj.sucMuffler.UAobj.getUA(),  compressorObj.expTemp.getInternalEnvironment(),compressorObj.sucMuffler.getSuctionMufflerAverageTemp());
	exportData << "UA SuctionMuffler-InternalEnvironment\t" << compressorObj.sucMuffler.UAobj.getUA() << endl;

	compressorObj.disMuffler.calcDischargeMufflerAverageTemp(compressorObj.expTemp.getDisChamberTemp(), compressorObj.expTemp.getDischargeMuffler());
	compressorObj.disMuffler.UAobj.calcUA(compressorObj.disMuffler.getDischargeMufflerAverageTemp(), compressorObj.expTemp.getInternalEnvironment());
	compressorObj.disMuffler.heatTransferRateObj.calcHeatTransferRate(compressorObj.disMuffler.UAobj.getUA(), compressorObj.disMuffler.getDischargeMufflerAverageTemp(), compressorObj.expTemp.getInternalEnvironment());
	exportData << "UA DischargeMuffler-InternalEnvironment\t" << compressorObj.disMuffler.UAobj.getUA() << endl;

	compressorObj.disChamber.UAobj.calcUA(compressorObj.expTemp.getDisChamberTemp(), compressorObj.expTemp.getInternalEnvironment());
	compressorObj.disChamber.heatTransferRateObj.calcHeatTransferRate(compressorObj.disChamber.UAobj.getUA(), compressorObj.expTemp.getDisChamberTemp(), compressorObj.expTemp.getInternalEnvironment());
	exportData << "UA DischargeChamber-InternalEnvironment\t" << compressorObj.disChamber.UAobj.getUA() << endl;

	compressorObj.bundy.calcBundyAverageTemp(compressorObj.expTemp.getDischargeMuffler(), compressorObj.expTemp.getDisLineTemp());
	compressorObj.bundy.UAobj.calcUA(compressorObj.bundy.getBundyAverageTemp(), compressorObj.expTemp.getInternalEnvironment());
	compressorObj.bundy.heatTransferRateObj.calcHeatTransferRate( compressorObj.bundy.UAobj.getUA(), compressorObj.bundy.getBundyAverageTemp(), compressorObj.expTemp.getInternalEnvironment()); 
	exportData << "UA Bundy-InternalEnvironment\t" << compressorObj.bundy.UAobj.getUA() << endl;

	compressorObj.internalEnvironment.UAobj.calcUA(compressorObj.expTemp.getInternalEnvironment(), compressorObj.expTemp.getShell());
	compressorObj.internalEnvironment.heatTransferRateObj.calcHeatTransferRate(compressorObj.internalEnvironment.UAobj.getUA(), compressorObj.expTemp.getInternalEnvironment(), compressorObj.expTemp.getShell());
	exportData << "UA InternalEnvironment-Shell\t" << compressorObj.internalEnvironment.UAobj.getUA() << endl;

	compressorObj.externalEnvironment.UAobj.calcUA(compressorObj.expTemp.getShell(), compressorObj.expTemp.getExternalEnvironment());
	compressorObj.externalEnvironment.heatTransferRateObj.calcHeatTransferRate(compressorObj.externalEnvironment.UAobj.getUA(), compressorObj.expTemp.getShell(), compressorObj.expTemp.getExternalEnvironment());
	exportData << "UA Shell-ExternalEnvironment\t" << compressorObj.externalEnvironment.UAobj.getUA() << endl;

}
