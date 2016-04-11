#include "Stator.h"

Stator::Stator()
{
	Input motorReaderData;

	motorReaderData.readMotorData();
	
	setMainWindingReferenceResistance(motorReaderData.getStatorMainWindingReferenceResistance());

	setMainWindingReactance(motorReaderData.getStatorMainWindingReactance());

	setThermalCoefficient(motorReaderData.getStatorThermalCoefficient());

	setReferenceTemperature(motorReaderData.getStatorReferenceTemperature());

	setMagnetizingReactance(motorReaderData.getStatorMagnetizingReactance());

	setIronResistance(motorReaderData.getStatorIronResistance());

	motor.setInputVoltage(motorReaderData.getMotorInputVoltage());
}


void Stator::calcMainWindingResistance(double thermalCoefficient, double referenceTemperature, double mainWindingReferenceResistance, double motorTemperature);
{
	mainWindingResistance = thermalCoefficient*mainWindingReferenceResistance*(motorTemperature - referenceTemperature) + mainWindingReferenceResistance;
}
void Stator::calcMainWindingImpedance(double mainWindingResistance, double mainWindingReactance);
{
	mainWindingImpedance = mainWindingImpedance(mainWindingResistance,mainWindingReactance);
}





void Stator::calcMainWindingCurrent(double inputVoltage, double equivalentImpedanceMagnitude)
{
	
}
