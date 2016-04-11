#include "Compressor.h"

Compressor::Compressor()
{
	plotCont = 0;
	multip =	0;
	it = 0; 
	cont = 0;
	n = 1;

}

void Compressor::silmulComp()
{
	ofstream expData;
	expData.open("NewRecip_Results.dat", ios::out);

	ofstream outData;
	outData.open("NewRecip_Output.dat", ios::out);

	sucSystObj.orifFact.creatOrifice();
	sucSystObj.valveFact.creatValve();

	disSystObj.orifFact.creatOrifice();
	disSystObj.valveFact.creatValve();

	sucSystObj.calcSucInicProp(systObj.getEvapTemp());
	disSystObj.calcDisInicProp(systObj.getCondTemp());

	systObj.calcEvapHDif();

	calcMechanIniProp();

	compChambObj.calcInicProp(mechanObj, sucSystObj.sucChambPress, sucSystObj.sucChambRho, sucSystObj.sucChambExpTemp);

	sucSystObj.orifFact.orifice[0].calcSpecHeatRatMed(sucSystObj.sucChambSpecHeatRat, disSystObj.disChambSpecHeatRat);
	disSystObj.orifFact.orifice[1].calcSpecHeatRatMed(sucSystObj.sucChambSpecHeatRat, disSystObj.disChambSpecHeatRat);

	sucSystObj.orifFact.orifice[0].calcCritPress();
	disSystObj.orifFact.orifice[1].calcCritPress();

	calcSimulPar();

	while(mechanObj.getTheta() < simulParObj.getFinTheta())
	{
		mechanObj.calcPos();
		mechanObj.calcVel();

		compChambObj.calcTemp(mechanObj, sucSystObj.sucChambH, disSystObj.disChambH, sucSystObj,disSystObj, simulParObj.getTimeStep(), leakObj.getMassFl());
		compChambObj.refrig.calcPress();

	    sucSystObj.execSimulSucMuffler(simulParObj.getDeltaTheta(), mechanObj.getShaftVel(), compChambObj.refrig.getTemp(), systObj.getIntEnvTemp(), sucSystObj.orifFact.orifice[0].getMassFl());
		//disSystObj.execSimulDisMuffler(simulParObj.getDeltaTheta(), mechanObj.getShaftVel(), compChambObj.refrig.getTemp(), systObj.getIntEnvTemp(), disSystObj.orifFact.orifice[1].getMassFl());

		compChambObj.calcGapFricFact(sucSystObj.sucLinePress, mechanObj.getVel());
		
		sucSystObj.orifFact.orifice[0].setTotSucFl(0);
		sucSystObj.orifFact.orifice[0].setTotSucBackf(0);

		disSystObj.orifFact.orifice[1].setTotDisFl(0);
		disSystObj.orifFact.orifice[1].setTotDisBackf(0);

		calcLeak();

		sucSystObj.calcSucValveDyn(compChambObj.refrig.getPress());
		disSystObj.calcDisValveDyn(compChambObj.refrig.getPress());

		sucSystObj.calcSucOrifMassFl(compChambObj.refrig.getPress(), compChambObj.refrig.getTemp());
		disSystObj.calcDisOrifMassFl(compChambObj.refrig.getPress(), compChambObj.refrig.getTemp());

		compChambObj.calcMassBal(sucSystObj.orifFact.orifice[0].getTotSucMassFl(), disSystObj.orifFact.orifice[1].getTotDisMassFl(), leakObj.getMassFl(), simulParObj.getTimeStep());

		sucSystObj.orifFact.orifice[0].setTotSucMassFl(0);
		disSystObj.orifFact.orifice[1].setTotDisMassFl(0);

		if(mechanObj.getTheta() >= simulParObj.getLastTheta())
		{
			if(sucSystObj.valveFact.valve[0].getDisp() <= 0)
			{
				sucSystObj.orifFact.orifice[0].setMassFl(0);
			}

			if(disSystObj.valveFact.valve[1].getDisp() <= 0)
			{
				disSystObj.orifFact.orifice[1].setMassFl(0);
			}

			leakObj.calcMassSum(simulParObj.getTimeStep());

			calcWork();

			postProcObj.calcGapPistonCylinderPotencyLose(compChambObj.getGapFricFact() , mechanObj.getVel());

			expResult(expData);

			cont++;
		}

		mechanObj.incremTheta(simulParObj.getDeltaTheta());

	}

	mechanObj.theta = 0;
}

void Compressor::calcMechanIniProp()
{
	mechanObj.calcShaftVel();
	mechanObj.calcSupDeadPt();
	mechanObj.calcVelMed();
	mechanObj.calcPos();
}

void Compressor::calcLeak()
{
	if(compChambObj.getShape() == "conic")
	{
		compChambObj.calcDistBottPistTop(mechanObj.getPos());
		compChambObj.calcDistBottPistPin();

		compChambObj.getGapPistTop();
		compChambObj.getGapPistPin();
		compChambObj.getGapPistBott();

		compChambObj.calcTopDiam();
		compChambObj.calcBottDiam();
	}

	compChambObj.calcLeakArea();
	leakObj.calcVel(compChambObj, sucSystObj.sucLinePress, compChambObj.refrig.getVisc(), mechanObj.getVel() );
	leakObj.calcMassFl(compChambObj.refrig.getRho(), compChambObj);
}

void Compressor::calcSimulPar()
{
	simulParObj.calcFinTheta();
	simulParObj.calcTimeStep(mechanObj.getShaftVel());
	simulParObj.calcLastTheta();


}

void Compressor::calcWork()
{
	workObj.setInicialProperties(compChambObj.refrig.getPress(), compChambObj.getVol());
	workObj.setWorkPres(compChambObj.refrig.getPress());
	workObj.setWorkVol(compChambObj.getVol());
	workObj.calcWorkMediaPres();
	workObj.calcRefrigerantWork();
	workObj.calcSucValveWork(sucSystObj.sucLinePress, sucSystObj.sucChambPress);
	workObj.calcSucChamberWork(sucSystObj.sucLinePress, sucSystObj.sucChambPress);

	workObj.calcDisValveWork(disSystObj.disLinePress, disSystObj.disChambPress);
	workObj.calcDisChamberWork(disSystObj.disLinePress, disSystObj.disChambPress);

	workObj.calcLeakWork(compChambObj.refrig.getRho(), compChambObj.refrig.getTemp(), leakObj.getMassFl(), simulParObj.getTimeStep());
	workObj.setOldWorkPres(compChambObj.refrig.getPress());
	workObj.setOldWorkVol(compChambObj.getVol());
}

void Compressor::expResult(ofstream &expData)
{
	double T, Y;

	T = 0.001745;

	Y  = T/simulParObj.getDeltaTheta(); 
	 
	if( multip*plotCont - multip*Y < 0.0000001) 
	{
		if(it == 0)
		{
			expData << "Angulo         ";
			expData << "Posicao     ";
			expData << "Volume      ";
			expData << "Posicao_Valvula_Succao      ";
			expData << "Velocidade_Valvula_Succao      ";
			expData << "Vazao_Massica_Valvula_Succao      ";
			expData << "Posicao_Valvula_Descarga      ";
			expData << "Velocidade_Valvula_Descarga      ";
			expData << "Vazao_Massica_Valvula_Descarga      ";
			expData << "Vazao_Massica_Folga_Pistao_Cilindro      ";
			expData << "Pressao_Cilindro      ";
			expData << "Pressao_Linha_Succao      ";
			expData << "Pressao_Linha_Descarga      " ;
			expData << "Pressao_Camara_Succao      ";
			expData << "Pressao_Camara_Descarga      ";
			expData << "Temperatura_Cilindro      " << endl;

			it++;
		}

		expData << (mechanObj.getTheta() - (simulParObj.getCyclesNum() -1)*2*ct.Pi )*180/ct.Pi << setw(8) << "";
		expData << mechanObj.getPos() << setw(13);
		expData << compChambObj.getVol()*10E5 <<  setw(19);

	
		expData << sucSystObj.valveFact.valve[0].getDisp()*1000	<< setw(30);
		expData << sucSystObj.valveFact.valve[0].getVel() << setw(33);
		expData << sucSystObj.orifFact.orifice[0].getMassFl()*1E+3 << setw(31);

		expData << disSystObj.valveFact.valve[1].getDisp()*1000	<< setw(30);
		expData << disSystObj.valveFact.valve[1].getVel() << setw(33);
		expData << disSystObj.orifFact.orifice[1].getMassFl()*1E+3 << setw(31);
	

		expData << "               ";
		
		expData << leakObj.getMassFl()*1E+3 << setw(33);
		expData << compChambObj.refrig.getPress()/100000 << setw(24);
		expData << sucSystObj.sucLinePress/100000  << setw(27);
		expData << disSystObj.disLinePress/100000  << setw(27);
		expData << sucSystObj.sucChambPress/100000  << setw(27);

		expData << disSystObj.disChambPress/100000  << setw(22);
	
		expData << compChambObj.refrig.getTemp() - 273.15;

		expData << endl;
		++n;

		plotCont = 0;
		multip++;
	}

	plotCont++;

}

void Compressor::execPostProc(ofstream &outData)
{
	//Suc
	postProcObj.calcMassSuctioned(sucSystObj.orifFact.orifice[0].getMassSumFl(), sucSystObj.orifFact.orifice[0].getMassSumBackf());
	postProcObj.calcSuctionRefluxLoses(sucSystObj.orifFact.orifice[0].getMassSumBackf(), mechanObj.getFreq());

	//Dis
	postProcObj.calcMassDischarged(disSystObj.orifFact.orifice[1].getMassSumFl(), disSystObj.orifFact.orifice[1].getMassSumBackf());
	postProcObj.calcDischargeRefluxLoses(disSystObj.orifFact.orifice[1].getMassSumBackf(), mechanObj.getFreq());

	postProcObj.calcIdealMassDischarged(compChambObj.getDispVol(), sucSystObj.sucLineRho);
	postProcObj.calcMassFlowDischarged(mechanObj.getFreq());
	postProcObj.calcSuperheatingLoses(sucSystObj.sucLineRho, sucSystObj.sucChambRho);
	postProcObj.calcIdealMassSuctioned(mechanObj.getFreq());
	postProcObj.calcIdealMassFlow(mechanObj.getFreq());
	postProcObj.calcIdealMassFlowSuctioned(mechanObj.getFreq());
	postProcObj.calcMassFlowSuctioned(mechanObj.getFreq());
	postProcObj.calcSuctionRestrictionLoses();
	postProcObj.calcSuctionTotalLoses();
	postProcObj.calcLeakLoses(leakObj.getMassSumFl(), mechanObj.getFreq());
	postProcObj.calcIdealMassFlowDischarged(mechanObj.getFreq());
	postProcObj.calcRefrigerationCapacity(systObj.getEvapHDif());
	postProcObj.calcMassFlowTotalLoses();
	postProcObj.calcDeadVolumePolitropicLoses(disSystObj.disChambPress, sucSystObj.sucChambPress, sucSystObj.sucChambRho, disSystObj.disChambRho, compChambObj.getDeadVol(), disSystObj.disLinePress, sucSystObj.sucLinePress, mechanObj.getFreq());
	postProcObj.calcDischargeRestrictionLoses();
	postProcObj.calcDischargeTotalLoses();
	postProcObj.calcAnotherLoses();
	bearObj.calcBearingsLos(motObj.expTemp);
	postProcObj.calcTransmissionPotencyLose(bearObj.getBearingsLos(), cont);
	
	postProcObj.calcIdealSpecificWork(sucSystObj.sucLinePress, sucSystObj.sucLineRho, disSystObj.disLinePress, sucSystObj.orifFact.orifice[0].getSpecHeatRatMed());

	postProcObj.calcSucValvePotencyLoses(workObj.getSuctionValveWork(), mechanObj.getFreq());
	postProcObj.calcSucChamberPotencyLoses(workObj.getSucChamberWork(), mechanObj.getFreq());
	postProcObj.calcDiscValvePotencyLoses(workObj.getDischargeValveWork(), mechanObj.getFreq());
	postProcObj.calcDiscChamberPotencyLoses(workObj.getDisChamberWork(), mechanObj.getFreq());
	postProcObj.calcCarnotCOP(systObj.getEvapTemp(), systObj.getCondTemp());
	postProcObj.calcCarnotPotency();

	postProcObj.calcSpecificWork(sucSystObj.sucLineTemp, sucSystObj.sucLineRho, disSystObj.disLinePress); 


	postProcObj.calcTeoricPotency();

	postProcObj.calcSuperHeatingSpecificWork(273.15 , sucSystObj.sucLinePress, disSystObj.disLinePress);


	postProcObj.calcSuperHeatingTeoricPotency();
	postProcObj.calcIndicatedPotency(workObj.getRefrigerantWork(),mechanObj.getFreq());
	postProcObj.calcLeakPotencyLoses(workObj.getLeakWork(), mechanObj.getFreq());
	postProcObj.calcEffectivePotency();
	postProcObj.calcRefrigerationCycleLoses();
	postProcObj.calcSuperheatingLoses();
	postProcObj.calcAnotherPotencyLoses();
	postProcObj.calcAxisPotency();
	motObj.calcEfficiency(postProcObj.axisPotency);
	postProcObj.calcConsumption(motObj.getEfficiency(), 0);
	postProcObj.calcMotorPotencyLoses(0);
	postProcObj.calcTotalPotencyLoses();
	postProcObj.calcEletricEfficiency();
	postProcObj.calcMechanicEfficiency();
	postProcObj.calcTermodynamicsEfficiency();
	postProcObj.calcCycleEfficiency();
	postProcObj.calcEnergyEfficiency();
	postProcObj.calcMassEfficiency();
	postProcObj.calcPerformanceEfficiency();
	postProcObj.calcCOP();
	postProcObj.calcEER();

	outData << "RELACOES MASSICAS:" << endl;
	outData << "FLUXO DE MASSA IDEAL\t" << "=\t" << postProcObj.idealMassFlow << endl;
	outData << "PERDAS:"<< endl;
	outData << "  SUPERAQUECIMENTO NA SUCCAO\t" << "=\t" << postProcObj.superheatingLoses << endl;
	outData << "  REFLUXO NA SUCCAO\t" << "=\t" << postProcObj.suctionRefluxLoses << endl;
	outData << "  VAZAMENTO PELA FOLGA\t" << "=\t" << postProcObj.leakLoses << endl;
	outData << "  REFLUXO NA DESCARGA\t" << "=\t" << postProcObj.dischargeRefluxLoses << endl;
	outData << "FLUXO DE MASSA REAL DO COMPRESSOR\t" << "=\t" << postProcObj.massFlowDischarged << endl;
	outData << "PERDA TOTAL NO FLUXO DE MASSA\t" << "=\t" << postProcObj.massFlowTotalLoses << endl;
	outData << " POTENCIAS:" << endl;
	outData << "POTENCIA IDEAL CARNOT\t" << "=\t" << postProcObj.CarnotPotency << endl;
	outData << "  PERDA NO CICLO\t" << "=\t" << postProcObj.refrigerationCycleLoses << endl;
	outData << "POTENCIA IDEAL ISENTROPICA\t" << "=\t" << postProcObj.teoricPotency << endl;
	outData << "  PERDA POR SUPERAQ.  0.0 [C]t" << "=\t" << postProcObj.superheatingPotencyLoses << endl;
	outData << "POTENCIA ISENTROPICA COM SUPERAQ.\t" << "=\t" << postProcObj.superHeatingTeoricPotency << endl;
	outData << "  PERDA POR VAZAMENTO FOLGA P/C\t" << "=\t" << postProcObj.leakPotencyLoses << endl;
	outData << "POTENCIA EFETIVA\t" << "=\t" << postProcObj.effectivePotency << endl;
	outData << "  PERDA NA VALVULA DE SUCCAO\t" << "=\t" << postProcObj.sucValvePotencyLoses << endl;
	outData << "  PERDA NO FILTRO DE SUCCAO\t" << "=\t" << postProcObj.sucChamberPotencyLoses << endl;
	outData << "  PERDA NA VALVULA DE DESCARGA\t" << "=\t" << postProcObj.discValvePotencyLoses << endl;
	outData << "  PERDA NO FILTRO DE DESCARGA\t" << "=\t" << postProcObj.discChamberPotencyLoses << endl;
	outData << "POTENCIA INDICADA\t" << "=\t" << postProcObj.indicadetPotency << endl;
	outData << "PERDA NA FOLGA PISTAO CILINDRO E H\t" << "=\t" << postProcObj.gapPistonCylinderPotencyLose/cont << endl;
	outData << "POTENCIA NO EIXO DO MOTOR\t" << "=\t" << postProcObj.axisPotency << endl;
	outData << "PERDA NO MOTOR ELETRICO\t" << "=\t" << postProcObj.motorPotencyLoses << endl;
	outData << "POTENCIA TOTAL" << endl;
	outData << "PERDA TOTAL DE POTENCIA\t" << "=\t" << postProcObj.totalPotencyLoses << endl;
	outData << endl;
	outData << "DESEMPENHO:\t" << "=\t" <<  endl;
	outData << "  EFICIENCIA ELETRICA\t" << "=\t" << postProcObj.eletricEfficiency << endl;
	outData << "  EFICIENCIA MECANICA\t" << "=\t" << postProcObj.mechanicEfficiency << endl;
	outData << "  EFICIENCIA TERMODINAMICA\t" << "=\t" << postProcObj.termodynamicsEfficiency << endl;
	outData << "  EFICIENCIA DO CICLO\t" << "=\t" << postProcObj.cycleEfficiency << endl;
	outData << "  EFICIENCIA ENERGETICA\t" << "=\t" << postProcObj.energyEfficiency << endl;
	outData << "  EFICIENCIA VOLUMETRICA\t" << "=\t" << postProcObj.massEfficiency << endl;
	outData << "CAPACIDADE DE REFRIGERACAO\t" << "=\t" << postProcObj.refrigerationCapacity << endl;
	outData << "CONSUMO\t" << "=\t" << postProcObj.consumption << endl;
	outData << "EER\t" << "=\t" << postProcObj.EER << endl;
}