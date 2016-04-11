#include "PostProcessing.h"

PostProcessing::PostProcessing()
{
	gapPistonCylinderPotencyLose = 0;
}

void PostProcessing::calcIdealMassDischarged(double displacementVolume, double suctionLineRho)
{
	idealMassDischarged = suctionLineRho*displacementVolume;
}

void PostProcessing::calcMassDischarged(double dischargeFluxMassSum, double dischargeRefluxMassSum)
{	
	massDischarged = dischargeFluxMassSum - dischargeRefluxMassSum;
}

void PostProcessing::calcMassFlowDischarged(double frequency)
{	
	massFlowDischarged = massDischarged*frequency;
}

void PostProcessing::calcSuperheatingLoses(double suctionLineRho, double suctionChamberRho)
{
	superheatingLoses = massFlowDischarged*(suctionLineRho/suctionChamberRho - 1);
}

void PostProcessing::calcIdealMassSuctioned(double frequency)
{
	idealMassSuctioned = idealMassDischarged - superheatingLoses/frequency;
}

void PostProcessing::calcMassSuctioned(double suctionFluxMassSum, double suctionRefluxMassSum)
{
	massSuctioned = suctionFluxMassSum - suctionRefluxMassSum;
}

void PostProcessing::calcIdealMassFlow(double frequency)
{
	idealMassFlow = idealMassDischarged*frequency;
}

void PostProcessing::calcIdealMassFlowSuctioned(double frequency)
{
	idealMassFlowSuctioned = idealMassSuctioned*frequency;
}

void PostProcessing::calcSuctionRefluxLoses(double suctionRefluxMassSum, double frequency)
{
	suctionRefluxLoses = suctionRefluxMassSum*frequency;
}

void PostProcessing::calcMassFlowSuctioned(double frequency)
{
	massFlowSuctioned = massSuctioned*frequency;
}

void PostProcessing::calcSuctionRestrictionLoses()
{
	suctionRestrictionLoses = idealMassFlowSuctioned - (massFlowSuctioned + suctionHeatingLoses + suctionRefluxLoses + deadVolumeLoses);
}

void PostProcessing::calcSuctionTotalLoses()
{
	suctionTotalLoses = suctionRefluxLoses + suctionHeatingLoses + deadVolumeLoses + suctionRestrictionLoses;
}

void PostProcessing::calcLeakLoses(double leakMassFlux, double frequency)
{
	leakLoses = leakMassFlux*frequency;
}

void PostProcessing::calcDeadVolumeLoses(double massSumDischargeClosed, double frequency)
{
	deadVolumeLoses = massSumDischargeClosed*frequency;
}

void PostProcessing::calcIdealMassFlowDischarged(double frequency)
{
	idealMassFlowDischarged = idealMassDischarged*frequency;
}

void PostProcessing::calcRefrigerationCapacity(double evaporatorEnthlapyDiference)
{
	refrigerationCapacity = massFlowDischarged*evaporatorEnthlapyDiference;
}

void PostProcessing::calcMassFlowTotalLoses()
{
	massFlowTotalLoses = idealMassFlow - massFlowDischarged;
} 

void PostProcessing::calcDeadVolumePolitropicLoses(double disChamberPressureValue,double sucChamberPressureValue ,double sucChamberRhoValue, double disChamberRhoValue,double deadVolumeValue, double discLinePressureValue, double sucLinePressureValue, double frequency)
{
	double politropicIndex;

	double deadVolumeDisplacementVolumeLose;

	politropicIndex = log(disChamberPressureValue/sucChamberPressureValue)/log((1/sucChamberRhoValue)/(1/disChamberRhoValue)); 

	deadVolumeDisplacementVolumeLose = deadVolumeValue*pow( (discLinePressureValue/sucLinePressureValue),(1/politropicIndex)) - deadVolumeValue;

	deadVolumePolitropicLoses = deadVolumeDisplacementVolumeLose*frequency*sucChamberRhoValue;
}

void PostProcessing::calcDischargeRefluxLoses(double dischargeRefluxMassSum, double frequency)
{
	dischargeRefluxLoses = dischargeRefluxMassSum*frequency;
}

void PostProcessing::calcDischargeRestrictionLoses()
{
	dischargeRestrictionLoses = idealMassFlowDischarged - (massDischarged + leakLoses + dischargeRefluxLoses +  deadVolumePolitropicLoses);
}

void PostProcessing::calcDischargeTotalLoses()
{
	dischargeTotalLoses = leakLoses + dischargeRefluxLoses + deadVolumePolitropicLoses + dischargeRestrictionLoses;
}

void PostProcessing::calcAnotherLoses()
{
	anotherLoses = massFlowTotalLoses - superheatingLoses - suctionRefluxLoses - leakLoses - dischargeRefluxLoses - deadVolumePolitropicLoses;
}


void PostProcessing::calcGapPistonCylinderPotencyLose(double frictionPistonCylinderValue, double pistonVelocity)
{
	gapPistonCylinderPotencyLose = gapPistonCylinderPotencyLose + frictionPistonCylinderValue*pistonVelocity;
}

void PostProcessing::calcTransmissionPotencyLose(double bearingLoses, int contador)
{
	transmissionPotencyLose = gapPistonCylinderPotencyLose/contador + bearingLoses;
}

void PostProcessing::calcIdealSpecificWork(double suctionLinePres, double suctionLineRho, double dischargeLinePres, double specificHeatsRatioMedia)
{
	idealSpecificWork = suctionLinePres*(1/suctionLineRho)*(specificHeatsRatioMedia/(specificHeatsRatioMedia - 1.0))*pow((dischargeLinePres/suctionLinePres),((specificHeatsRatioMedia - 1.0)/specificHeatsRatioMedia) - 1.0);
}

void PostProcessing::calcSucValvePotencyLoses(double suctionValveWork, double frequency)
{
	sucValvePotencyLoses = suctionValveWork*frequency;

	
}

void PostProcessing::calcSucChamberPotencyLoses(double sucChamberWork, double frequency)
{
	sucChamberPotencyLoses = sucChamberWork*frequency;
}

void PostProcessing::calcDiscValvePotencyLoses(double dischargeValveWork, double frequency)
{
	discValvePotencyLoses = dischargeValveWork*frequency;
}

void PostProcessing::calcDiscChamberPotencyLoses(double disChamberWork, double frequency)
{
	discChamberPotencyLoses = disChamberWork*frequency;
}

void PostProcessing::calcCarnotCOP(double evaporatonTemperature, double condesationTemperature)
{
	CarnotCOP = (evaporatonTemperature)/((condesationTemperature) - (evaporatonTemperature));
}

void PostProcessing::calcCarnotPotency()
{
	 CarnotPotency = refrigerationCapacity/CarnotCOP;
}

void PostProcessing::calcSpecificWork(double sucLineTempValue, double sucLineRhoValue, double disLinePresValue)
{
	double sucLineEntalphy;
	
	refrig.setTemp(sucLineTempValue);
	refrig.setRho(sucLineRhoValue);
	refrig.calcH();
	refrig.calcS();

	sucLineEntalphy = refrig.getH();

	refrig.setPress(disLinePresValue);
	refrig.calcIsentProp();

	specificWork = refrig.getH() - sucLineEntalphy;
}

void PostProcessing::calcTeoricPotency()
{
	teoricPotency = specificWork*massFlowDischarged;
}

void PostProcessing::calcSuperHeatingSpecificWork(double sucLineTempValue, double sucLinePresValue, double disLinePresValue)
{
	double sucLineEntalphy;

	refrig.setTemp(sucLineTempValue);
	refrig.setPress(sucLinePresValue);
	refrig.calcRho();
	
	refrig.calcH();
	refrig.calcS();
	sucLineEntalphy = refrig.getH();

	refrig.setPress(disLinePresValue);
	refrig.calcIsentProp();

	superHeatingSpecificWork = refrig.getH() - sucLineEntalphy;
}

void PostProcessing::calcSuperHeatingTeoricPotency()
{
	superHeatingTeoricPotency = superHeatingSpecificWork*massFlowDischarged;
}

void PostProcessing::calcIndicatedPotency(double refrigerantWork, double frequency)
{
	indicadetPotency = refrigerantWork*frequency;
}

void PostProcessing::calcLeakPotencyLoses(double leakWork, double frequency)
{	
	leakPotencyLoses = leakWork*frequency;
}

void PostProcessing::calcEffectivePotency()
{
	effectivePotency = indicadetPotency - (sucValvePotencyLoses + discValvePotencyLoses + sucChamberPotencyLoses + discChamberPotencyLoses);
}

void PostProcessing::calcRefrigerationCycleLoses()
{
	refrigerationCycleLoses = teoricPotency - CarnotPotency;
}

void PostProcessing::calcSuperheatingLoses()
{
	superheatingPotencyLoses = superHeatingTeoricPotency - teoricPotency;
}

void PostProcessing::calcAnotherPotencyLoses()
{
	anotherPotencyLoses = effectivePotency - teoricPotency - leakPotencyLoses - superheatingLoses;
}

void PostProcessing::calcAxisPotency()
{
	axisPotency = indicadetPotency + transmissionPotencyLose;
}


void PostProcessing::calcConsumption(double motorEfficiency, double inicialConsumeValue)
{
	consumption = axisPotency/motorEfficiency + inicialConsumeValue;
}

void PostProcessing::calcMotorPotencyLoses(double inicialConsumeValue)
{
	motorPotencyLoses = consumption - axisPotency - inicialConsumeValue;
}

void PostProcessing::calcTotalPotencyLoses()
{
	totalPotencyLoses =  consumption - CarnotPotency;
}

void PostProcessing::calcEletricEfficiency()
{
	eletricEfficiency = axisPotency/ consumption;
}

void PostProcessing::calcMechanicEfficiency()
{
	mechanicEfficiency = indicadetPotency/axisPotency;
}

void PostProcessing::calcTermodynamicsEfficiency()
{
	termodynamicsEfficiency = teoricPotency/indicadetPotency;
}

void PostProcessing::calcCycleEfficiency()
{
	cycleEfficiency = CarnotPotency/teoricPotency;
}

void PostProcessing::calcEnergyEfficiency()
{
	energyEfficiency = CarnotPotency/ consumption;
}

void PostProcessing::calcMassEfficiency()
{
	massEfficiency = massDischarged/idealMassDischarged;
}

void PostProcessing::calcPerformanceEfficiency()
{
	performanceEfficiency = (massFlowDischarged*teoricPotency)/(idealMassFlow* consumption);
}

void PostProcessing::calcCOP()
{
	COP = refrigerationCapacity/consumption;
}

void PostProcessing::calcEER()
{
	EER = COP*cte.potencyUnit;
}



