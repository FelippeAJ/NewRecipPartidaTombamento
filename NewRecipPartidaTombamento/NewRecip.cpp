#include "NewRecip.h"

NewRecip::NewRecip()
{
	
}

void NewRecip::executeCompressorSimulation()
{
	compressorObj.simulateCompressor();
}

void NewRecip::executeThermalBalance()
{
	thermalBalanceObj.calcThermalBalance(compressorObj);
}