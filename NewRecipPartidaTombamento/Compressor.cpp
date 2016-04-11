#include "Compressor.h"

Compressor::Compressor()
:iterative(0), n(1), contador(0), plotContador(0), multiplo(0)
{

}



void Compressor::simulateCompressor()
{
	int sucBackflowCte = 0;

	int stickingForceIndice = -1;

	ofstream exportData;
	exportData.open("NewRecip_Results.dat", ios::out);

	ofstream outputData;
	outputData.open("NewRecip_Output.dat", ios::out);
	
	calcPropertiesOfComponents();

	calcPropertiesOfMechanism();

	calcSimulationParameters();
	
	compressionChamberObj.calcInicialProperties(mechanism, sucChamber.refrigerant.getPressure()) ;

	multiploOrificesObj.creatMultipleOrifices();

	multiploOrificesObj.calcInicialProperties(sucChamber.refrigerant.getSpecificHeatsRatio(), disChamber.refrigerant.getSpecificHeatsRatio());

	while(mechanism.crank.getTheta() < simulParameters.getFinalTheta())
	{
		mechanism.calcPosition();
		mechanism.calcVelocity();
		
		compressionChamberObj.calcTemperature(mechanism, sucChamber.refrigerant.getEnthalpy(), disChamber.refrigerant.getEnthalpy(), multiploOrificesObj,simulParameters.getTimeStep());  
		compressionChamberObj.cyl.refrigerant.calcPressure();

		mechanism.calcGapFrictionFactor(expTemp.getCylinderWallTemp(), sucLine.refrigerant.getPressure(), compressionChamberObj.cyl.getBore(), compressionChamberObj.cyl.refrigerant.getPressure());

		multiploOrificesObj.orificesSet.setTotalSucFlux(0);
		multiploOrificesObj.orificesSet.setTotalSucBackflow(0);
		multiploOrificesObj.orificesSet.setTotalDisFlux(0);
		multiploOrificesObj.orificesSet.setTotalDisBackflow(0);

		compressionChamberObj.calcLeak(mechanism.getPosition(), sucLine.refrigerant.getPressure());

		
		if(multiploOrificesObj.dynSystemFact.dynamicSystem[1].getDisplacement() > 0)
		{
			stickingForceIndice = 1;
		}

		
		if(multiploOrificesObj.dynSystemFact.dynamicSystem[0].getDisplacement() > 0)
		{
			stickingForceIndice = 0;
		}
		

		multiploOrificesObj.calcValveDynamic(compressionChamberObj.cyl.refrigerant.getPressure(), sucChamber, disChamber, stickingForceIndice);
		
		
		multiploOrificesObj.calcMassFlow(compressionChamberObj.cyl.refrigerant.getPressure(), compressionChamberObj.cyl.refrigerant.getTemperature(), sucChamber, disChamber);

		

		compressionChamberObj.cyl.calcMassBalance(multiploOrificesObj.orificesSet.getTotalSucMassFlow(), multiploOrificesObj.orificesSet.getTotalDisMassFlow() , compressionChamberObj.leak.getMassFlow(), simulParameters.getTimeStep());
	
		multiploOrificesObj.orificesSet.setTotalSucMassFlow(0);
		multiploOrificesObj.orificesSet.setTotalDisMassFlow(0);

		if(mechanism.crank.getTheta() >= simulParameters.getLastTheta())
		{
			for(int j = 0; j < multiploOrificesObj.getNumberOfOrifices(); j++)
			{
				if(multiploOrificesObj.dynSystemFact.dynamicSystem[j].getDisplacement() <= 0)
				{
					multiploOrificesObj.orificeFact.orifice[j].setMassFlow(0);
				}

				multiploOrificesObj.orificeFact.orifice[j].calcMassSum(simulParameters.getTimeStep());
			}


			compressionChamberObj.leak.calcMassSum(simulParameters.getTimeStep());

			calcWork();

			calcEnthalpyFluxInCompressionChamber();

			postProcessing.calcGapPistonCylinderPotencyLose(mechanism.getGapFrictionFactor(), mechanism.getVelocity());

			exportResults(exportData);

			contador++;

			
		}

		mechanism.crank.incrementTheta(simulParameters.getDeltaTheta());
	}

	executePostProcessing(outputData);

	calcEnthalpyFluxOfComponents();

	calcInputOutputEnergyRateSumOfComponents();

	mechanism.crank.theta = 0;
	//cout << "Ef. Eletrica = " << postProcessing.eletricEfficiency*100 << endl;
}

void Compressor::calcPropertiesOfComponents()
{
	sucLine.calcProperties(expTemp.getEvaporationTemp(), expTemp.getSucLineTemp());

	sucMuffler.calcProperties(expTemp.getSucChamberTemp(), sucLine.refrigerant.getPressure());

	internalEnvironment.calcProperties(expTemp.getInternalEnvironment(), sucLine.refrigerant.getPressure());

	sucChamber.calcProperties(expTemp.getEvaporationTemp(), expTemp.getSucChamberTemp());
	sucChamber.refrigerant.calcSpecificHeatsRatio();

	disChamber.calcProperties(expTemp.getCondesationTemp(), expTemp.getDisChamberTemp());
	disChamber.refrigerant.calcSpecificHeatsRatio();

	disMuffler.calcProperties(expTemp.getCondesationTemp(), expTemp.getDischargeMuffler());

	bundy.calcProperties(expTemp.getCondesationTemp(), expTemp.getDisLineTemp());

	disLine.calcProperties(expTemp.getCondesationTemp(), expTemp.getDisLineTemp());

	evaporator.calcEnthlapyDiference(expTemp.getSubcoolingTemp(), expTemp.getSuperheatingTemp(), expTemp.getEvaporationTemp());
}

void Compressor::calcPropertiesOfMechanism()
{
	mechanism.axis.calcVelocity();
	mechanism.calcSuperiorDeadPoint();
	mechanism.calcVelocityMedia();
	mechanism.calcPosition();
	mechanism.calcContactLength();
}

void Compressor::calcSimulationParameters()
{
	simulParameters.calcFinalTheta();
	simulParameters.calcTimeStep(mechanism.axis.getVelocity());
	simulParameters.calcLastTheta();
}

void Compressor::calcWork()
{
	work.setInicialProperties(compressionChamberObj.cyl.refrigerant.getPressure(), compressionChamberObj.cyl.getVolume());
	work.setWorkPres(compressionChamberObj.cyl.refrigerant.getPressure());
	work.setWorkVol(compressionChamberObj.cyl.getVolume());
	work.calcWorkMediaPres();
	work.calcRefrigerantWork();
	work.calcSucValveWork(sucLine.refrigerant.getPressure(), sucChamber.refrigerant.getPressure());
	work.calcSucChamberWork(sucLine.refrigerant.getPressure(), sucChamber.refrigerant.getPressure());
	work.calcDisValveWork(disLine.refrigerant.getPressure(), disChamber.refrigerant.getPressure());
	work.calcDisChamberWork(disLine.refrigerant.getPressure(), disChamber.refrigerant.getPressure());
	work.calcLeakWork(compressionChamberObj.cyl.refrigerant.getRho(), compressionChamberObj.cyl.refrigerant.getTemperature(), compressionChamberObj.leak.getMassFlow(), simulParameters.getTimeStep());
	work.setOldWorkPres(compressionChamberObj.cyl.refrigerant.getPressure());
	work.setOldWorkVol(compressionChamberObj.cyl.getVolume());
}

void Compressor::calcEnthalpyFluxInCompressionChamber()
{
	compressionChamberObj.cyl.calcEnthalpyFluxToInternalEnvironment(compressionChamberObj.leak.getMassFlow(), simulParameters.getTimeStep());
	
	for(int i = 0; i < multiploOrificesObj.getNumberOfOrifices(); i++)
	{
		if(multiploOrificesObj.dynSystemFact.dynamicSystem[i].getDisplacement() > 0)
		{
			if(multiploOrificesObj.orificeFact.orifice[i].getDirection() == "suction")
			{
				compressionChamberObj.cyl.calcEnthalpyFluxToSuctionChamber(multiploOrificesObj.orificeFact.orifice[i].getBackFlow(), simulParameters.getTimeStep()); 
			}
			else
			{
				compressionChamberObj.cyl.calcEnthalpyFluxToDischargeChamber(multiploOrificesObj.orificeFact.orifice[i].getFlux(), simulParameters.getTimeStep()); 
			}
		}
	}
}

void Compressor::calcEnthalpyFluxOfComponents()
{
	for(int i = 0; i < multiploOrificesObj.getNumberOfOrifices(); i++)
	{
		if(multiploOrificesObj.orificeFact.orifice[i].getDirection() == "suction")
		{	
			sucChamber.calcEnthalpyFluxToCylinder(multiploOrificesObj.orificeFact.orifice[i].getMassSumFlux(), mechanism.axis.getFrequency());
		}
		else
		{
			disChamber.calcEnthalpyFluxToCylinder(multiploOrificesObj.orificeFact.orifice[i].getMassSumBackflow(), mechanism.axis.getFrequency());
		}
	}
	
	compressionChamberObj.cyl.calcEnthalpyFluxToInternalEnvironmentAverage(compressionChamberObj.cyl.getEnthalpyFluxToInternalEnvironment(), mechanism.axis.getFrequency());
	compressionChamberObj.cyl.calcEnthalpyFluxToDischargeChamberAverage(compressionChamberObj.cyl.getEnthalpyFluxToDischargeChamber(), mechanism.axis.getFrequency());
	compressionChamberObj.cyl.calcEnthalpyFluxToSuctionChamberAverage(compressionChamberObj.cyl.getEnthalpyFluxToSuctionChamber(), mechanism.axis.getFrequency());
	sucLine.calcEnthalpyFluxtoSuctionMuffler(postProcessing.massFlowDischarged, simulParameters.getDirectSuctionFactor());
	sucLine.calcEnthalpyFluxtoInternalEnvironment(postProcessing.massFlowDischarged);
	disLine.calcEnthalpyFluxToOutlet(postProcessing.massFlowDischarged);
	disChamber.calcEnthalpyFluxToDischargeMuffler(postProcessing.massFlowDischarged);
	disMuffler.calcEnthalpyFluxtoBundy(postProcessing.massFlowDischarged);
	bundy.calcEnthalpyFluxToDischargeLine(postProcessing.massFlowDischarged);
	internalEnvironment.calcEnthalpyFluxToSuctionMuffler(postProcessing.leakLoses, postProcessing.massFlowDischarged, simulParameters.getDirectSuctionFactor());
	sucMuffler.calcEnthalpyFluxToInternalEnvironment(compressionChamberObj.leak.getMassSumBackFlow(), mechanism.axis.getFrequency());
	internalEnvironment.calcEnthalpyFluxToCylinder(compressionChamberObj.leak.getMassSumBackFlow(), mechanism.axis.getFrequency());
}

void Compressor::calcInputOutputEnergyRateSumOfComponents()
{

	motor.UAobj.setInputEnergyRateSum(0);
	motor.UAobj.setOutputEnergyRateSum(0);
	motor.calcHeat(postProcessing.consumption);
	motor.UAobj.calcInputEnergyRateSum(1, motor.getHeat());
	
	compressionChamberObj.cyl.UAobj.setInputEnergyRateSum(0);
	compressionChamberObj.cyl.UAobj.setOutputEnergyRateSum(0);
	//compressionChamberObj.cyl.UAobj.calcInputEnergyRateSum(6,sucChamber.getEnthalpyFluxToCylinder(), disChamber.getEnthalpyFluxToCylinder(), internalEnvironment.getEnthalpyFluxToCylinder(), postProcessing.indicadetPotency, postProcessing.gapPistonCylinderPotencyLose/contador, bearings.getBearingsLoses());
	compressionChamberObj.cyl.UAobj.calcInputEnergyRateSum(6,sucChamber.getEnthalpyFluxToCylinder(), disChamber.getEnthalpyFluxToCylinder(), internalEnvironment.getEnthalpyFluxToCylinder(), postProcessing.indicadetPotency, postProcessing.gapPistonCylinderPotencyLose/contador, bearings.getLoses());
	//compressionChamberObj.cyl.UAobj.calcInputEnergyRateSum(5,sucChamber.getEnthalpyFluxToCylinder(), disChamber.getEnthalpyFluxToCylinder(), internalEnvironment.getEnthalpyFluxToCylinder(), postProcessing.indicadetPotency, postProcessing.gapPistonCylinderPotencyLose/contador);
	compressionChamberObj.cyl.UAobj.calcOutputEnergyRateSum(3, compressionChamberObj.cyl.getEnthalpyFluxToDischargeChamberAverage(), compressionChamberObj.cyl.getEnthalpyFluxToSuctionChamberAverage(), compressionChamberObj.cyl.getEnthalpyFluxToInternalEnvironmentAverage());

	sucMuffler.UAobj.setInputEnergyRateSum(0);
	sucMuffler.UAobj.setOutputEnergyRateSum(0);
	sucMuffler.UAobj.calcInputEnergyRateSum(3, sucLine.getEnthalpyFluxtoSuctionMuffler(), compressionChamberObj.cyl.getEnthalpyFluxToSuctionChamberAverage(), internalEnvironment.getEnthalpyFluxToSuctionMuffler());
	sucMuffler.UAobj.calcOutputEnergyRateSum(2, sucChamber.getEnthalpyFluxToCylinder(),sucMuffler.getEnthalpyFluxToInternalEnvironment()); 

	disMuffler.UAobj.setInputEnergyRateSum(0);
	disMuffler.UAobj.setOutputEnergyRateSum(0);
	disMuffler.UAobj.calcInputEnergyRateSum(1, disChamber.getEnthalpyFluxToDischargeMuffler());
	disMuffler.UAobj.calcOutputEnergyRateSum(1, disMuffler.getEnthalpyFluxtoBundy()); 

	disChamber.UAobj.setInputEnergyRateSum(0);
	disChamber.UAobj.setOutputEnergyRateSum(0);
	disChamber.UAobj.calcInputEnergyRateSum(1, compressionChamberObj.cyl.getEnthalpyFluxToDischargeChamberAverage()); 
	disChamber.UAobj.calcOutputEnergyRateSum(2, disChamber.getEnthalpyFluxToDischargeMuffler(), disChamber.getEnthalpyFluxToCylinder());

	bundy.UAobj.setInputEnergyRateSum(0);
	bundy.UAobj.setOutputEnergyRateSum(0);
	bundy.UAobj.calcInputEnergyRateSum(1, disMuffler.getEnthalpyFluxtoBundy());
	bundy.UAobj.calcOutputEnergyRateSum(1, bundy.getEnthalpyFluxToDischargeLine());


	internalEnvironment.UAobj.setInputEnergyRateSum(0);
	internalEnvironment.UAobj.setOutputEnergyRateSum(0);

	double calcEnergyRateDifferenceSucMuffler = 0;
	double calcEnergyRateDifferenceCompChamber = 0;
	double calcEnergyRateDifferenceDisChamber = 0;
	double calcEnergyRateDifferenceDisMuffler = 0;
	double calcEnergyRateDifferenceBundy = 0;
	double calcEnergyRateDifferenceMotor = 0;
	double calcEnergyRateDifferenceInternalEnvironment = 0;

	calcEnergyRateDifferenceSucMuffler = sucMuffler.UAobj.getOutputEnergyRateSum() - sucMuffler.UAobj.getInputEnergyRateSum();
	calcEnergyRateDifferenceCompChamber = compressionChamberObj.cyl.UAobj.getInputEnergyRateSum() - compressionChamberObj.cyl.UAobj.getOutputEnergyRateSum();
	calcEnergyRateDifferenceDisChamber = disChamber.UAobj.getInputEnergyRateSum() - disChamber.UAobj.getOutputEnergyRateSum();
	calcEnergyRateDifferenceDisMuffler = disMuffler.UAobj.getInputEnergyRateSum() - disMuffler.UAobj.getOutputEnergyRateSum();
	calcEnergyRateDifferenceBundy = bundy.UAobj.getInputEnergyRateSum() - bundy.UAobj.getOutputEnergyRateSum();
	calcEnergyRateDifferenceMotor = motor.UAobj.getInputEnergyRateSum() - motor.UAobj.getOutputEnergyRateSum();

	internalEnvironment.UAobj.calcInputEnergyRateSum(7, calcEnergyRateDifferenceCompChamber, calcEnergyRateDifferenceDisChamber, calcEnergyRateDifferenceDisMuffler, calcEnergyRateDifferenceBundy, calcEnergyRateDifferenceMotor, sucLine.getEnthalpyFluxtoInternalEnvironment(), compressionChamberObj.cyl.getEnthalpyFluxToInternalEnvironmentAverage());
	internalEnvironment.UAobj.calcOutputEnergyRateSum(3, calcEnergyRateDifferenceSucMuffler, sucLine.getEnthalpyFluxtoSuctionMuffler(), internalEnvironment.getEnthalpyFluxToSuctionMuffler());
	
	calcEnergyRateDifferenceInternalEnvironment = internalEnvironment.UAobj.getInputEnergyRateSum() - internalEnvironment.UAobj.getOutputEnergyRateSum();

	//internalEnvironment.UAobj.calcInputEnergyRateSum(1,externalEnvironment.heatTransferRateObj.getHeatTransferRate());

	externalEnvironment.UAobj.setInputEnergyRateSum(0);
	//externalEnvironment.UAobj.setOutputEnergyRateSum(0);
	externalEnvironment.UAobj.calcInputEnergyRateSum(1, calcEnergyRateDifferenceInternalEnvironment);
	//externalEnvironment.UAobj.calcOutputEnergyRateSum(1, bundy.getEnthalpyFluxToDischargeLine());
	//externalEnvironment.UAobj.calcUA(expTemp.getShell(), expTemp.getExternalEnvironment());
	//externalEnvironment.heatTransferRateObj.calcHeatTransferRate(externalEnvironment.UAobj.getUA(), expTemp.getShell(), expTemp.getExternalEnvironment());

}


void Compressor::exportResults(ofstream &exportData)
{
	double T, Y;

	/*T = 1.0*cte.Pi/180;

	Y = T/simulParameters.getDeltaTheta();

	cout << plotContador/Y << endl;
	if( plotContador/Y < 1E-3)
	{
		cout << mechanism.crank.getTheta()*180/cte.Pi;
	}

	plotContador++;*/
	

	T = 0.001745;

	Y  = T/simulParameters.getDeltaTheta(); 
	 

	/*if( multiplo*plotContador - multiplo*Y < 0.001) 
	{
		cout << mechanism.crank.getTheta() << endl;

		plotContador = 0;
		multiplo++;
	}

	plotContador++;*/

	//Constants cte;

	//if((mechanism.crank.getTheta() - (n*simulParameters.getFinalTheta()/360 - 0.001)) > 0.000001)
	if( multiplo*plotContador - multiplo*Y < 0.0000001) 
	{
		if(iterative == 0)
		{
			exportData << "Angulo     ";
			exportData << "Posicao     ";
			exportData << "Volume      ";
			exportData << "Posicao_Valvula_Succao      ";
			exportData << "Velocidade_Valvula_Succao      ";
			exportData << "Vazao_Massica_Valvula_Succao      ";
			exportData << "Posicao_Valvula_Descarga      ";
			exportData << "Velocidade_Valvula_Descarga      ";
			exportData << "Vazao_Massica_Valvula_Descarga      ";
			exportData << "Vazao_Massica_Folga_Pistao_Cilindro      ";
			exportData << "Pressao_Cilindro      ";
			exportData << "Pressao_Linha_Succao      ";
			exportData << "Pressao_Linha_Descarga      " ;
			exportData << "Pressao_Camara_Succao      ";
			exportData << "Pressao_Camara_Descarga      ";
			exportData << "Temperatura_Cilindro      " << endl;

			iterative++;
		}

		exportData << (mechanism.crank.getTheta() - (simulParameters.getCyclesNumber() -1)*2*cte.Pi )*180/cte.Pi << setw(4) << "";
		exportData << mechanism.getPosition() << setw(13);
		exportData << compressionChamberObj.cyl.getVolume()*10E5 <<  setw(19);

		for(int i = 0; i < multiploOrificesObj.getNumberOfOrifices(); i++)
		{
			exportData << multiploOrificesObj.dynSystemFact.dynamicSystem[i].getDisplacement()*1000 << setw(30);
			exportData << multiploOrificesObj.dynSystemFact.dynamicSystem[i].getVelocity() << setw(33);
			exportData << multiploOrificesObj.orificeFact.orifice[i].getMassFlow()*1E+3 << setw(31);
		}

		exportData << "               ";
		
		exportData << compressionChamberObj.leak.getMassFlow()*1E+3 << setw(33);
		exportData << compressionChamberObj.cyl.refrigerant.getPressure()/100000 << setw(24);
		exportData << sucLine.refrigerant.getPressure()/100000  << setw(27);
		exportData << disLine.refrigerant.getPressure()/100000  << setw(27);
		exportData << sucChamber.refrigerant.getPressure()/100000  << setw(27);
		exportData << disChamber.refrigerant.getPressure()/100000  << setw(30);
		exportData << compressionChamberObj.cyl.refrigerant.getTemperature() - 273.15  << setw(30);
		exportData << work.sucValveWork*1000  << setw(30);
		exportData << work.disValveWork*1000;


		exportData << endl;
		++n;

		plotContador = 0;
		multiplo++;
	}

	plotContador++;

}





void Compressor::executePostProcessing(ofstream &outputData)
{
	POLOIO POLOOobj("input.dat");

	/*for(int i = 0; i < multiploOrificesObj.getNumberOfOrifices(); i++)
	{
		if(multiploOrificesObj.orificeFact.orifice[i].getDirection() == "suction")
		{	
			postProcessing.calcMassSuctioned(multiploOrificesObj.orificeFact.orifice[i].getMassSumFlux(), multiploOrificesObj.orificeFact.orifice[i].getMassSumBackflow());
			postProcessing.calcSuctionRefluxLoses(multiploOrificesObj.orificeFact.orifice[i].getMassSumBackflow(), mechanism.axis.getFrequency());
		}
		else
		{
			postProcessing.calcMassDischarged(multiploOrificesObj.orificeFact.orifice[i].getMassSumFlux(), multiploOrificesObj.orificeFact.orifice[i].getMassSumBackflow());
			postProcessing.calcDischargeRefluxLoses(multiploOrificesObj.orificeFact.orifice[i].getMassSumBackflow(), mechanism.axis.getFrequency());
		}
	}*/


		
	postProcessing.calcMassSuctioned(multiploOrificesObj.orificeFact.orifice[0].getMassSumFlux(), multiploOrificesObj.orificeFact.orifice[0].getMassSumBackflow());
	postProcessing.calcSuctionRefluxLoses(multiploOrificesObj.orificeFact.orifice[0].getMassSumBackflow(), mechanism.axis.getFrequency());
	
	postProcessing.calcMassDischarged(multiploOrificesObj.orificeFact.orifice[1].getMassSumFlux(), multiploOrificesObj.orificeFact.orifice[1].getMassSumBackflow());
	postProcessing.calcDischargeRefluxLoses(multiploOrificesObj.orificeFact.orifice[1].getMassSumBackflow(), mechanism.axis.getFrequency());


	postProcessing.calcIdealMassDischarged(compressionChamberObj.cyl.getDisplacementVolume(), sucLine.refrigerant.getRho());
	postProcessing.calcMassFlowDischarged(mechanism.axis.getFrequency());
	postProcessing.calcSuperheatingLoses(sucLine.refrigerant.getRho(), sucChamber.refrigerant.getRho());
	postProcessing.calcIdealMassSuctioned(mechanism.axis.getFrequency());
	postProcessing.calcIdealMassFlow(mechanism.axis.getFrequency());
	postProcessing.calcIdealMassFlowSuctioned(mechanism.axis.getFrequency());
	postProcessing.calcMassFlowSuctioned(mechanism.axis.getFrequency());
	postProcessing.calcSuctionRestrictionLoses();
	postProcessing.calcSuctionTotalLoses();
	postProcessing.calcLeakLoses(compressionChamberObj.leak.getMassSumFlux(), mechanism.axis.getFrequency());
	postProcessing.calcIdealMassFlowDischarged(mechanism.axis.getFrequency());
	postProcessing.calcRefrigerationCapacity(evaporator.getEnthalpyDiference());
	postProcessing.calcMassFlowTotalLoses();
	postProcessing.calcDeadVolumePolitropicLoses(disChamber.refrigerant.getPressure(), sucChamber.refrigerant.getPressure(), sucChamber.refrigerant.getRho(), disChamber.refrigerant.getRho(), compressionChamberObj.cyl.getDeadVolume(), disLine.refrigerant.getPressure(), sucLine.refrigerant.getPressure(), mechanism.axis.getFrequency());
	postProcessing.calcDischargeRestrictionLoses();
	postProcessing.calcDischargeTotalLoses();
	postProcessing.calcAnotherLoses();
	bearings.calcBearingsLoses();
	//postProcessing.calcTransmissionPotencyLose(bearings.getBearingsLoses(), contador);
	postProcessing.calcTransmissionPotencyLose(bearings.getLoses(), contador);
	postProcessing.calcIdealSpecificWork(sucLine.refrigerant.getPressure(), sucLine.refrigerant.getRho(), disLine.refrigerant.getPressure(), multiploOrificesObj.orificesSet.getSpecificHeatsRatioMedia());
	postProcessing.calcSucValvePotencyLoses(work.getSuctionValveWork(), mechanism.axis.getFrequency());
	postProcessing.calcSucChamberPotencyLoses(work.getSucChamberWork(), mechanism.axis.getFrequency());
	postProcessing.calcDiscValvePotencyLoses(work.getDischargeValveWork(), mechanism.axis.getFrequency());
	postProcessing.calcDiscChamberPotencyLoses(work.getDisChamberWork(), mechanism.axis.getFrequency());
	postProcessing.calcCarnotCOP(expTemp.getEvaporationTemp(), expTemp.getCondesationTemp());
	postProcessing.calcCarnotPotency();
	postProcessing.calcSpecificWork(sucLine.refrigerant.getTemperature(), sucLine.refrigerant.getRho(), disLine.refrigerant.getPressure()); 
	postProcessing.calcTeoricPotency();
	postProcessing.calcSuperHeatingSpecificWork(POLOOobj.getVariable("suction_chamber", "right") + 273.15, sucLine.refrigerant.getPressure(), disLine.refrigerant.getPressure());
	postProcessing.calcSuperHeatingTeoricPotency();
	postProcessing.calcIndicatedPotency(work.getRefrigerantWork(),mechanism.axis.getFrequency());
	postProcessing.calcLeakPotencyLoses(work.getLeakWork(), mechanism.axis.getFrequency());
	postProcessing.calcEffectivePotency();
	postProcessing.calcRefrigerationCycleLoses();
	postProcessing.calcSuperheatingLoses();
	postProcessing.calcAnotherPotencyLoses();
	postProcessing.calcAxisPotency();
	motor.calcEfficiency(postProcessing.axisPotency);
	postProcessing.calcConsumption(motor.getEfficiency(), 0);
	postProcessing.calcMotorPotencyLoses(0);
	postProcessing.calcTotalPotencyLoses();
	postProcessing.calcEletricEfficiency();
	postProcessing.calcMechanicEfficiency();
	postProcessing.calcTermodynamicsEfficiency();
	postProcessing.calcCycleEfficiency();
	postProcessing.calcEnergyEfficiency();
	postProcessing.calcMassEfficiency();
	postProcessing.calcPerformanceEfficiency();
	postProcessing.calcCOP();
	postProcessing.calcEER();


	outputData << "RELACOES MASSICAS:" << endl;
	outputData << "FLUXO DE MASSA IDEAL\t" << "=\t" << postProcessing.idealMassFlow << endl;
	outputData << "PERDAS:"<< endl;
	outputData << "  SUPERAQUECIMENTO NA SUCCAO\t" << "=\t" << postProcessing.superheatingLoses << endl;
	outputData << "  REFLUXO NA SUCCAO\t" << "=\t" << postProcessing.suctionRefluxLoses << endl;
	outputData << "  VAZAMENTO PELA FOLGA\t" << "=\t" << postProcessing.leakLoses << endl;
	outputData << "  REFLUXO NA DESCARGA\t" << "=\t" << postProcessing.dischargeRefluxLoses << endl;
	outputData << "FLUXO DE MASSA REAL DO COMPRESSOR\t" << "=\t" << postProcessing.massFlowDischarged << endl;
	outputData << "PERDA TOTAL NO FLUXO DE MASSA\t" << "=\t" << postProcessing.massFlowTotalLoses << endl;
	outputData << " POTENCIAS:" << endl;
	outputData << "POTENCIA IDEAL CARNOT\t" << "=\t" << postProcessing.CarnotPotency << endl;
	outputData << "  PERDA NO CICLO\t" << "=\t" << postProcessing.refrigerationCycleLoses << endl;
	outputData << "POTENCIA IDEAL ISENTROPICA\t" << "=\t" << postProcessing.teoricPotency << endl;
	outputData << "  PERDA POR SUPERAQ. A\t " << POLOOobj.getVariable("suction_chamber", "right") << " [C]" << "=\t" << postProcessing.superheatingPotencyLoses << endl;
	outputData << "POTENCIA ISENTROPICA COM SUPERAQ.\t" << "=\t" << postProcessing.superHeatingTeoricPotency << endl;
	outputData << "  PERDA POR VAZAMENTO FOLGA P/C\t" << "=\t" << postProcessing.leakPotencyLoses << endl;
	outputData << "POTENCIA EFETIVA\t" << "=\t" << postProcessing.effectivePotency << endl;
	outputData << "  PERDA NA VALVULA DE SUCCAO\t" << "=\t" << postProcessing.sucValvePotencyLoses << endl;
	outputData << "  PERDA NO FILTRO DE SUCCAO\t" << "=\t" << postProcessing.sucChamberPotencyLoses << endl;
	outputData << "  PERDA NA VALVULA DE DESCARGA\t" << "=\t" << postProcessing.discValvePotencyLoses << endl;
	outputData << "  PERDA NO FILTRO DE DESCARGA\t" << "=\t" << postProcessing.discChamberPotencyLoses << endl;
	outputData << "POTENCIA INDICADA\t" << "=\t" << postProcessing.indicadetPotency << endl;
	outputData << "PERDA NA FOLGA PISTAO CILINDRO E H\t" << "=\t" << postProcessing.gapPistonCylinderPotencyLose/contador << endl;
	outputData << "PERDA NA TRANSMISSAO\t" << "=\t" << postProcessing.transmissionPotencyLose << endl;
	outputData << "POTENCIA NO EIXO DO MOTOR\t" << "=\t" << postProcessing.axisPotency << endl;
	outputData << "PERDA NO MOTOR ELETRICO\t" << "=\t" << postProcessing.motorPotencyLoses << endl;
	outputData << "POTENCIA TOTAL" << endl;
	outputData << "PERDA TOTAL DE POTENCIA\t" << "=\t" << postProcessing.totalPotencyLoses << endl;
	outputData << endl;
	outputData << "DESEMPENHO:\t" << "=\t" <<  endl;
	outputData << "  EFICIENCIA ELETRICA\t" << "=\t" << postProcessing.eletricEfficiency << endl;
	outputData << "  EFICIENCIA MECANICA\t" << "=\t" << postProcessing.mechanicEfficiency << endl;
	outputData << "  EFICIENCIA TERMODINAMICA\t" << "=\t" << postProcessing.termodynamicsEfficiency << endl;
	outputData << "  EFICIENCIA DO CICLO\t" << "=\t" << postProcessing.cycleEfficiency << endl;
	outputData << "  EFICIENCIA ENERGETICA\t" << "=\t" << postProcessing.energyEfficiency << endl;
	outputData << "  EFICIENCIA VOLUMETRICA\t" << "=\t" << postProcessing.massEfficiency << endl;
	outputData << "CAPACIDADE DE REFRIGERACAO\t" << "=\t" << postProcessing.refrigerationCapacity << endl;
	outputData << "CONSUMO\t" << "=\t" << postProcessing.consumption << endl;
	outputData << "EER\t" << "=\t" << postProcessing.EER << endl;

}
