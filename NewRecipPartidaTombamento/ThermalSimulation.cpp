#include "ThermalSimulation.h"


ThermalSimulation::ThermalSimulation()
{
	POLOIO POLOIOobj("input.dat");
	TLRNCE = POLOIOobj.getVariable("TLRNCE", "right");
	RELAX =  POLOIOobj.getVariable("RELAX", "right");

	RESID = 0;
	CONVER = 0;
}

void ThermalSimulation::setNewTemperatures()
{
	POLOIO POLOOobj("input.dat");

	newTemperatures[0] = POLOOobj.getVariable("shell", "right"); 
	newTemperatures[1] = POLOOobj.getVariable("suction_chamber", "right"); 
	newTemperatures[2] = POLOOobj.getVariable("cylinder_wall", "right"); 
	newTemperatures[3] = POLOOobj.getVariable("discharge_chamber", "right"); 
	newTemperatures[4] = POLOOobj.getVariable("discharge_muffler", "right"); 
	newTemperatures[5] = POLOOobj.getVariable("discharge_line", "right");
	newTemperatures[6] = POLOOobj.getVariable("internal_environment", "right"); 
	newTemperatures[7] = POLOOobj.getVariable("motor", "right"); 
}

void ThermalSimulation::setOldTemperature()
{
	oldTemperatures = newTemperatures;
}

void ThermalSimulation::dimensionVectors()
{
	newTemperatures.resize(8);
	residuo.resize(8);
	temperaturesPertubaded.resize(8);
	residuoPertubaded.resize(residuo.size(), newTemperatures);
}

void ThermalSimulation::calcResiduo()
{	
	POLOIO POLOIOobj("NewRecip_UAs.dat");

	Compressor compressorObj1;
	compressorObj1.simulateCompressor();

	residuo[0] =  POLOIOobj.getVariable("InternalEnvironment-Shell", "right")*( newTemperatures[6] - newTemperatures[0] ) -  POLOIOobj.getVariable("Shell-ExternalEnvironment", "right")*(newTemperatures[0] - (compressorObj1.expTemp.getExternalEnvironment() -273.15));

	residuo[1] =  POLOIOobj.getVariable("SuctionMuffler-InternalEnvironment", "right")*( newTemperatures[6] - ((compressorObj1.expTemp.getSucLineTemp()-273.15) + newTemperatures[1] )/2 ) + compressorObj1.sucMuffler.UAobj.getInputEnergyRateSum() - compressorObj1.sucMuffler.UAobj.getOutputEnergyRateSum() ;
		
	residuo[2] =  POLOIOobj.getVariable("Cylinder-InternalEnvironment", "right")*(newTemperatures[2] - newTemperatures[6]) - compressorObj1.compressionChamberObj.cyl.UAobj.getInputEnergyRateSum() + compressorObj1.compressionChamberObj.cyl.UAobj.getOutputEnergyRateSum();
	
	residuo[3] =  POLOIOobj.getVariable("DischargeChamber-InternalEnvironment", "right")*(newTemperatures[3] - newTemperatures[6]) -  compressorObj1.disChamber.UAobj.getInputEnergyRateSum() + compressorObj1.disChamber.UAobj.getOutputEnergyRateSum();
	
	residuo[4] =  POLOIOobj.getVariable("DischargeMuffler-InternalEnvironment", "right")*((newTemperatures[4] + newTemperatures[3] )/2 - newTemperatures[6]) - compressorObj1.disMuffler.UAobj.getInputEnergyRateSum() + compressorObj1.disMuffler.UAobj.getOutputEnergyRateSum();
	
	residuo[5] =  POLOIOobj.getVariable("Bundy-InternalEnvironment", "right")*((newTemperatures[5] + newTemperatures[4])/2 - newTemperatures[6]) - compressorObj1.bundy.UAobj.getInputEnergyRateSum() + compressorObj1.bundy.UAobj.getOutputEnergyRateSum();
	
	residuo[6] =  - POLOIOobj.getVariable("InternalEnvironment-Shell", "right")*( newTemperatures[6] - newTemperatures[0] ) + compressorObj1.internalEnvironment.UAobj.getInputEnergyRateSum() - compressorObj1.internalEnvironment.UAobj.getOutputEnergyRateSum();
	
	residuo[7] =  -POLOIOobj.getVariable("Motor-InternalEnvironment", "right")*(newTemperatures[7] -  newTemperatures[6])  +  compressorObj1.postProcessing.consumption - compressorObj1.bearings.getLoses() - compressorObj1.postProcessing.indicadetPotency - compressorObj1.postProcessing.gapPistonCylinderPotencyLose/compressorObj1.contador;


	stopCriteria = compressorObj1.postProcessing.consumption;
	
		cout << " ---------------------------------------------- " << endl;
		cout << "Res TH = " << residuo[0] << endl;
		cout << "Res TSC = " << residuo[1] << endl;
		cout << "Res TW = " << residuo[2] << endl;
		cout << "Res TDC = " << residuo[3] << endl;
		cout << "Res TDM = " << residuo[4] << endl;
		cout << "Res TDL = " << residuo[5] << endl;
		cout << "Res TIE = " << residuo[6] << endl;
		cout << "Res TMOT = " << residuo[7] << endl;

}

void ThermalSimulation::calcResiduoPertubaded()
{
	POLOIO POLOIOobj("NewRecip_UAs.dat");
	POLOIO POLOIOobj2("input.dat");		
	
	double iterator2 = 0;

	for(int i = 0; i < newTemperatures.size(); i++)
	{
	
		iterator2++;

		//cout << "Iteracao Jacobiano = " << iterator2 << endl;

		newTemperatures[i] = newTemperatures[i]*1.003;

		POLOIOobj2.writeVariable("shell", newTemperatures[0] , "right"); 
		POLOIOobj2.writeVariable("suction_chamber",newTemperatures[1] , "right");
		POLOIOobj2.writeVariable("cylinder_wall",newTemperatures[2], "right");
		POLOIOobj2.writeVariable("discharge_chamber",newTemperatures[3] , "right");
		POLOIOobj2.writeVariable("discharge_muffler",newTemperatures[4] , "right");
		POLOIOobj2.writeVariable("discharge_line",newTemperatures[5]  , "right");
		POLOIOobj2.writeVariable("internal_environment",newTemperatures[6], "right");
		POLOIOobj2.writeVariable("motor",newTemperatures[7] , "right");
		
		Compressor compressorObj2;
		compressorObj2.simulateCompressor();

		residuoPertubaded[0][i] =(POLOIOobj.getVariable("InternalEnvironment-Shell", "right")*( newTemperatures[6] - newTemperatures[0] ) -  POLOIOobj.getVariable("Shell-ExternalEnvironment", "right")*(newTemperatures[0] - (compressorObj2.expTemp.getExternalEnvironment() -273.15)));

		residuoPertubaded[1][i] =( POLOIOobj.getVariable("SuctionMuffler-InternalEnvironment", "right")*( newTemperatures[6] - ((compressorObj2.expTemp.getSucLineTemp()-273.15) + newTemperatures[1] )/2 ) + compressorObj2.sucMuffler.UAobj.getInputEnergyRateSum() - compressorObj2.sucMuffler.UAobj.getOutputEnergyRateSum()) ;
	
		residuoPertubaded[2][i] =(POLOIOobj.getVariable("Cylinder-InternalEnvironment", "right")*(newTemperatures[2] - newTemperatures[6]) - compressorObj2.compressionChamberObj.cyl.UAobj.getInputEnergyRateSum() + compressorObj2.compressionChamberObj.cyl.UAobj.getOutputEnergyRateSum());
	
		residuoPertubaded[3][i] =(POLOIOobj.getVariable("DischargeChamber-InternalEnvironment", "right")*(newTemperatures[3] - newTemperatures[6]) -  compressorObj2.disChamber.UAobj.getInputEnergyRateSum() + compressorObj2.disChamber.UAobj.getOutputEnergyRateSum());
	
		residuoPertubaded[4][i] =(POLOIOobj.getVariable("DischargeMuffler-InternalEnvironment", "right")*((newTemperatures[4] + newTemperatures[3] )/2 - newTemperatures[6]) - compressorObj2.disMuffler.UAobj.getInputEnergyRateSum() + compressorObj2.disMuffler.UAobj.getOutputEnergyRateSum());
	
		residuoPertubaded[5][i] =(POLOIOobj.getVariable("Bundy-InternalEnvironment", "right")*((newTemperatures[5] + newTemperatures[4])/2 - newTemperatures[6]) - compressorObj2.bundy.UAobj.getInputEnergyRateSum() + compressorObj2.bundy.UAobj.getOutputEnergyRateSum());
			
		residuoPertubaded[6][i] =  - POLOIOobj.getVariable("InternalEnvironment-Shell", "right")*( newTemperatures[6] - newTemperatures[0] ) + compressorObj2.internalEnvironment.UAobj.getInputEnergyRateSum() - compressorObj2.internalEnvironment.UAobj.getOutputEnergyRateSum();

		residuoPertubaded[7][i] =(-POLOIOobj.getVariable("Motor-InternalEnvironment", "right")*(newTemperatures[7] -  newTemperatures[6])  +  compressorObj2.postProcessing.consumption - compressorObj2.bearings.getLoses() - compressorObj2.postProcessing.indicadetPotency - compressorObj2.postProcessing.gapPistonCylinderPotencyLose/compressorObj2.contador);

		newTemperatures[i] = oldTemperatures[i];
	}
}

void ThermalSimulation::executeThermalSimulation()
{
	dimensionVectors();

	vector<double> deltaTValues;

	POLOIO POLOIOobj2("input.dat");

	setNewTemperatures();

	setOldTemperature();

	double iterator = 0;

	while(CONVER == 0)
	{
		
		iterator++;
	
		cout << "Iteracao NewtonRaphson = " << iterator << endl;

		cout << " ---------------------------------------------- " << endl;
		cout << "TH = " << newTemperatures[0] << endl;
		cout << "TSC = " << newTemperatures[1] << endl;
		cout << "TW = " << newTemperatures[2] << endl;
		cout << "TDC = " << newTemperatures[3] << endl;
		cout << "TDM = " << newTemperatures[4] << endl;
		cout << "TDL = " << newTemperatures[5] << endl;
		cout << "TIE = " << newTemperatures[6] << endl;
		cout << "TMOT = " << newTemperatures[7] << endl;

		calcResiduo();

		RESID = 1;

		for(int i = 0; i < residuo.size(); i++)
		{
			if(abs(residuo[i]) > abs(TLRNCE*stopCriteria))
			{
				RESID = 0;
			}
		}

		if(RESID == 1)
		{
			CONVER = 1;
		}
		else
		{

			calcResiduoPertubaded();

			jacobianObj.calcJacobianMatrix(residuoPertubaded, residuo, newTemperatures, 0.003);

			newtonRaphsonObj.calcDeltaT(jacobianObj.getJacobianMatrix(), residuo);

			deltaTValues = newtonRaphsonObj.getDeltaT();


			for(int i =0; i < deltaTValues.size(); i++)
			{
				newTemperatures[i] = oldTemperatures[i] - deltaTValues[i]*RELAX;
			}

			setOldTemperature();

			POLOIOobj2.writeVariable("shell", newTemperatures[0] , "right"); 
			POLOIOobj2.writeVariable("suction_chamber",newTemperatures[1] , "right");
			POLOIOobj2.writeVariable("cylinder_wall",newTemperatures[2], "right");
			POLOIOobj2.writeVariable("discharge_chamber",newTemperatures[3] , "right");
			POLOIOobj2.writeVariable("discharge_muffler",newTemperatures[4] , "right");
			POLOIOobj2.writeVariable("discharge_line",newTemperatures[5]  , "right");
			POLOIOobj2.writeVariable("internal_environment",newTemperatures[6], "right");
			POLOIOobj2.writeVariable("motor",newTemperatures[7] , "right");

			
			CONVER = 1;

			for(int i = 0; i < deltaTValues.size(); i++)
			{
				if(abs(deltaTValues[i]) > abs( newTemperatures[i]*TLRNCE*0.01))
				{
					CONVER = 0;
				}

			}
		}
	}



}



