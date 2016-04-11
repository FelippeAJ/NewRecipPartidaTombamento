#ifndef NEWRECIP_H
#define NEWRECIP_H

#include <iostream>

#include "Compressor.h"
#include "ThermalBalance.h"

using namespace std;

class NewRecip
{
public:
	NewRecip();

	void executeCompressorSimulation();
	void executeThermalBalance();

	Compressor compressorObj;
	ThermalBalance thermalBalanceObj;

protected:



};

#endif