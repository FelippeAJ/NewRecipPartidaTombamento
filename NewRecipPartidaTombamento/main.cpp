#include <iostream>
#include <fstream>
#include "Input.h"
#include "NewRecip.h"
#include "Compressor.h"
#include "ThermalSimulation.h"
#include "SimulationParameters.h"


using namespace std;


int main()
{

	loadRefprop();

	Input refrigerantReader;
	refrigerantReader.readRefrigerantData();

	setRefrigerant(refrigerantReader.refrigerantName);

	Compressor compressorObj;

	ThermalBalance thermalBalanceObj;

	ThermalSimulation thermalSimulationObj;

	SimulationParameters simulParameters;

	compressorObj.simulateCompressor();

	if(simulParameters.getThermalBalanceFlag() == 1)
	{
	thermalBalanceObj.calcThermalBalance(compressorObj);
	}
	
	cout << "Direct Suction Factor = " << simulParameters.getDirectSuctionFactor() << endl;

	if(simulParameters.getThermalSimulationFlag() == 1)
	{
	thermalSimulationObj.executeThermalSimulation();
	}

	system("PAUSE");
	return 0;
}

