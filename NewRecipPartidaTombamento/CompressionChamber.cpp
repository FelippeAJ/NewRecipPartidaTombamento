#include "CompressionChamber.h"

CompressionChamber::CompressionChamber()
{

}

void CompressionChamber::calcInicialProperties(Mechanism mechanism, double sucChamberPressure)
{
	cyl.calcArea();

	if(mechanism.getMechanism() == "crank_rod")
	{
		cyl.calcDisplacementVolume(2*mechanism.crank.getEccentricity());
	}
	else
	if(mechanism.getMechanism() == "sinusoidal")
	{
		cyl.calcDisplacementVolume(mechanism.getStroke());
	}

	cyl.calcVolume(mechanism.getSuperiorDeadPoint(), mechanism.getPosition()); 
	cyl.refrigerant.setTemperature(experimentalTemperatures.getSucChamberTemp());
	cyl.refrigerant.setPressure(sucChamberPressure);
	cyl.refrigerant.calcRho();
	cyl.refrigerant.calcMass(cyl.getVolume());

	piston.calcDiameter(cyl.getBore(), leak.getGap());

}

void CompressionChamber::calcTemperature(Mechanism mechanismObj, double sucChamberEnthalpy, double disChamberEnthalpy, MultipleOrifices multiploOrificesObj, double timeStep)
{
	cyl.calcVolume(mechanismObj.getSuperiorDeadPoint(),  mechanismObj.getPosition());
	cyl.refrigerant.calcRho(cyl.getVolume());
	cyl.refrigerant.calcViscosityThermalConductivity(mechanismObj.crank.getTheta());
	cyl.refrigerant.calcSpecificHeats();
	cyl.refrigerant.calcEntalphy();
	cyl.refrigerant.calcDpresDtemp();

	admNumbers.calcReynolds(cyl.refrigerant.getRho(),  mechanismObj.getVelocityMedia(), cyl.getBore(), cyl.refrigerant.getViscosity());
	admNumbers.calcPrandt(cyl.refrigerant.getViscosity(), cyl.refrigerant.getCp(), cyl.refrigerant.getThermalConductivity());
	admNumbers.calcNusselt();

	heatTransf.calcArea(cyl.getDeadVolume(), cyl.getBore(),  mechanismObj.getSuperiorDeadPoint(),  mechanismObj.getPosition(), cyl.getArea());
	heatTransf.calcConvectionCoef(admNumbers.getNusselt(), cyl.refrigerant.getThermalConductivity(), cyl.getBore());

	cyl.calcDerivateVolume( mechanismObj.getVelocity());
	cyl.calcDerivateTemperature(sucChamberEnthalpy, disChamberEnthalpy,  multiploOrificesObj.orificesSet.getTotalSucFlux(),  multiploOrificesObj.orificesSet.getTotalSucBackflow(),  multiploOrificesObj.orificesSet.getTotalDisFlux(),  multiploOrificesObj.orificesSet.getTotalDisBackflow());
	cyl.refrigerant.calcTemperatureExplicitily(cyl.getDerivateTemperature(), timeStep);
}

void CompressionChamber::calcLeak(double mechanismPosition, double sucLinePressure)
{
	if(cyl.getCylinder() == "conic")
	{
		piston.calcDistCylBottomPistonTop(mechanismPosition, cyl.getAxisDistance());
		piston.calcDistCylBottomPistonPin();

		leak.calcGapPistonTop();
		leak.calcGapPistonPin();
		leak.calcGapPistonBottom();
		leak.calcTopDiameter();
		leak.calcBottomDiameter();
	}

	leak.calcArea();
	leak.calcVelocity(cyl.refrigerant.getPressure(), sucLinePressure, cyl.refrigerant.getViscosity());
	leak.calcMassFlow(cyl.refrigerant.getRho());
}


