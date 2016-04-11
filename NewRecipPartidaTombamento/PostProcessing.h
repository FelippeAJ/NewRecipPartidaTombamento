#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <cmath>
#include "Constants.h"
#include "Refrigerant.h"


class PostProcessing
{
public:
	PostProcessing();

// MASSA IDEAL LIBERADA	

	void calcIdealMassDischarged(double displacementVolume, double suctionLineRho);

// MASSA LIBERADA

	void calcMassDischarged(double dischargeFluxMassSum, double dischargeRefluxMassSum);

// FLUXO DE MASSA REAL

	void calcMassFlowDischarged(double frequency);

// PERDAS POR SUPERAQUECIMENTO NA SUCCAO

	void calcSuperheatingLoses(double suctionLineRho, double suctionChamberRho);

// MASSA IDEAL QUE PASSA PELA SUCCAO

	void calcIdealMassSuctioned(double frequency);

// MASSA REAL QUE PASSA PELA SUCCAO	
	
	void calcMassSuctioned(double suctionFluxMassSum, double suctionRefluxMassSum);

// FLUXO DE MASSA IDEAL					

	void calcIdealMassFlow(double frequency);		

// FLUXO DE MASSA IDEAL SUCCIONADA		
     
	void calcIdealMassFlowSuctioned(double frequency);

// PERDA POR REFLUXO NA SUCCAO			
     
	void calcSuctionRefluxLoses(double suctionRefluxMassSum, double frequency);

// PERDA POR AQUECIMENTO DURANTE A SUCCAO	
      
	void calcSuctionSuperheatingLoses(double suctionLineRho, double suctionChamberRho);

// PERDA DEVIDO A MASSA JA EXISTENTE NO CILINDRO		
      
	void calcExistentMassLoses(double dischargeRefluxMassSum, double frequency);

// FLUXO DE MASSA REAL PELA SUCCAO			
     
	void calcMassFlowSuctioned(double frequency);

// PERDA POR RETRICAO DO FLUXO DE MASSA NA SUCCAO						
      
	void calcSuctionRestrictionLoses();

// PERDA TOTAL NA SUCCAO

	void calcSuctionTotalLoses();
     
// PERDA DEVIDO AO VAZAMENTO
    
	void calcLeakLoses(double leakMassFlux, double frequency);

// VOLUME DESLOCADO PERDIDO DEVIDO AO VOLUME MORTO
     
	void calcDeadVolumeLoses(double massSumDischargeClosed, double frequency);

// FLUXO DE MASSA IDEAL A DESCARREGAR
     
	void calcIdealMassFlowDischarged(double frequency);

// CAPACIDADE DE REFRIGERACAO (WATT)					

    void calcRefrigerationCapacity(double evaporatorEnthlapyDiference);

// PERDA TOTAL NO FLUXO DE MASSA
     
	void calcMassFlowTotalLoses();

// PERDA DEVIDO AO VOLUME MORTO CALCULADO POLITROPICAMENTE
      
	void calcDeadVolumePolitropicLoses(double disChamberPressureValue,double sucChamberPressureValue ,double sucChamberRhoValue, double disChamberRhoValue,double deadVolumeValue, double discLinePressureValue, double sucLinePressureValue, double frequency);

// PERDA POR REFLUXO NA DESCARGA						

    void calcDischargeRefluxLoses(double dischargeRefluxMassSum, double frequency);  

// PERDA POR RESTRICAO NA DESCARGA										

     void calcDischargeRestrictionLoses();

// PERDA TOTAL NA DESCARGA												
      
	void calcDischargeTotalLoses();

// PERDAS POR RESTRICAO, AQUECIMENTO E DEVIDO A MASSA RESTANTE NO CILINDRO		
      
	void calcAnotherLoses();

// PERDA DE POTENCIA NA FOLGA PISTAO CILINDRO
     
	void calcGapPistonCylinderPotencyLose(double frictionPistonCylinderValue, double pistonVelocity);

// PERDA DE POTENCIA NA TRANSMISSAO
     
	void calcTransmissionPotencyLose(double bearingLoses, int contador);

// TRABALHO ESPECIFICO IDEAL NECESSARIO AO GAS

	void calcIdealSpecificWork(double suctionLinePres, double suctionLineRho, double dischargeLinePres, double specificHeatsRatioMedia);
      
// POTENCIA PERDIDA NA VALVULA DE SUCCAO		
      
	void calcSucValvePotencyLoses(double suctionValveWork, double frequency);

// POTENCIA PERDIDA NO FILTRO DE SUCCAO			
      
	void calcSucChamberPotencyLoses(double sucChamberWork, double frequency);

// POTENCIA PERDIDA NA VALVULA DE DESCARGA		
      
	void calcDiscValvePotencyLoses(double dischargeValveWork, double frequency);

// POTENCIA PERDIDA NO FILTRO DE DESCARGA		
     
	void calcDiscChamberPotencyLoses(double disChamberWork, double frequency);

// COP CARNOT														

	void calcCarnotCOP(double evaporatonTemperature, double condesationTemperature);

// POTENCIA TEORICA CARNOT											

	void calcCarnotPotency();

// TRABALHO ESPECÍFICO DE COMPRESSAO ISENTROPICA
     
	//void calcSpecificWork(double TLS, double PLS, double TLD, double PLD, double TDC, double TC);
	void calcSpecificWork(double sucLineTempValue, double sucLineRhoValue, double disLinePresValue);

// POTENCIA TEORICA COM BASE EM COMPRESSAO ISENTROPICA
     
	void calcTeoricPotency();


// TRABALHO ESPECÍFICO DE COMPRESSAO ISENTROPICA COM SUPERAQUEC.
     
	//void calcSuperHeatingSpecificWork(double sucLineTempValue, double sucLinePresValue, double disLinePresValue);

	void calcSuperHeatingSpecificWork(double sucLineTempValue, double sucLinePresValue, double disLinePresValue);

// POTENCIA TEORICA COM BASE EM COMPRESSAO ISENTROPICA COM SUPERAQUEC.
      
	void calcSuperHeatingTeoricPotency();


// POTENCIA INDICADA
     
	void calcIndicatedPotency(double refrigerantWork, double frequency);

// POTENCIA GASTA PELO GAS QUE VAZOU PELA FOLGA PISTAO-CILINDRO
      
	void calcLeakPotencyLoses(double leakWork, double frequency);

// POTENCIA EFETIVA
      
	void calcEffectivePotency();

// PERDA NO CICLO DE REFRIGERAÇÃO
      
	void calcRefrigerationCycleLoses();

// PERDA NO SUPERAQUECIMENTO
     
	void calcSuperheatingLoses();

// PERDA TERMODINAMICA - OUTRAS PERDAS
      
	void calcAnotherPotencyLoses();

// POTENCIA NO EIXO
      
	void calcAxisPotency();

// CONSUMO
      
	void calcConsumption(double motorEfficiency, double inicialConsumeValue);

// PERDA DE POTENCIA NO MOTOR ELETRICO
      
	void calcMotorPotencyLoses(double inicialConsumeValue);

// PERDA TOTAL DE POTENCIA
     
	void calcTotalPotencyLoses();

// RENDIMENTO ELETRICO
     
	void calcEletricEfficiency();

// RENDIMENTO MECANICO
      
	void calcMechanicEfficiency();

// RENDIMENTO TERMODINAMICO
      
	void calcTermodynamicsEfficiency();

// RENDIMENTO DO CICLO
      
	void calcCycleEfficiency();

// RENDIMENTO DE ENERGIA
      
	void calcEnergyEfficiency();

// RENDIMENTO DE MASSA
      
	void calcMassEfficiency();

// RENDIMENTO DE DESEMPENHO
      
	void calcPerformanceEfficiency();

// CALCULO DO COEFICIENTE DE PERFORMANCE
      
	void calcCOP();

// CALCULO DO EER
      
	void calcEER();


	Constants cte;

	Refrigerant refrig;






	

//protected:
	double transmissionPotencyLose;
	double specificWork;
	double teoricPotency;
	double superHeatingSpecificWork;
	double superHeatingTeoricPotency;
	double leakPotencyLoses;
	double anotherPotencyLoses;
	double axisPotency;
	double motorEfficiency;
	double consumption;
	double motorPotencyLoses;
	double eletricEfficiency;
	double mechanicEfficiency;
	double energyEfficiency;
	double massEfficiency;
	double performanceEfficiency;
	double COP;
	double EER;

	





	double gapPistonCylinderPotencyLose;
	double anotherLoses;
	double massFlowTotalLoses;
	double idealMassFlow;
	double idealMassDischarged;
	double idealMassFlowDischarged;
	double massDischarged;
	double massFlowDischarged;
	double superheatingLoses;
	double idealMassSuctioned;
	double idealMassFlowSuctioned;
	double massSuctioned;
	double massFlowSuctioned;
	double suctionRefluxLoses;
	double suctionRestrictionLoses;
	double suctionHeatingLoses;
	double suctionTotalLoses;
	double dischargeRefluxLoses;
	double dischargeRestrictionLoses;
	double dischargeLoses;
	double dischargeTotalLoses;
	double leakLoses;
	double deadVolumeLoses;
	double deadVolumePolitropicLoses;
	double sucValvePotencyLoses;
	double discValvePotencyLoses;
	double sucChamberPotencyLoses;
	double discChamberPotencyLoses;
	double refrigerationCapacity;
	double idealSpecificWork;
	double CarnotPotency;
	double CarnotCOP;
	double indicadetPotency;
	double effectivePotency;
	double refrigerationCycleLoses;
	double superheatingPotencyLoses;
	double termodynamicLoses;
	double totalPotencyLoses;
	double termodynamicsEfficiency;
	double cycleEfficiency;
	
};

#endif