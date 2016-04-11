#include "Input.h"

Input::Input()
{
	mechanismDisplacement = "crank_rod";
	axisReversibility = 0;
	mechanismStroke = 0;
	cylinderDeadVolume = 0;
	cylinderLength = 0;
	cylinderConicLength = 0;
	leakShellPressure = -1.0E5;
	leakSeal = "absent";
	orificesNumber = 0;
	motorCoefNumber = 0;
}

Input::~Input()
{

}

void Input::readRefrigerantData()
{
	ifstream refrigerantReader;

	refrigerantReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(refrigerantReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(refrigerantReader, comment);
		}
		else
		if(tempName1 == "refrigerant")
		{
			refrigerantReader >> refrigerantName;
		}
		else
		if(tempName1 == "viscosity_thermalcond")
		{
			refrigerantReader >> refrigViscosityThermalCondCalc;
		}	
	}
}

string Input::getRefrigViscThermalCondCalc()
{
	return refrigViscosityThermalCondCalc;
}

void Input::readMechanismData()
{
	ifstream mechanismReader;

	mechanismReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(mechanismReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(mechanismReader , comment);
		}
		else
		if(tempName1 == "mechanism_displacement") 
		{
			mechanismReader >> mechanismDisplacement;
		}
		else
		if(tempName1 == "axis_reversibility")
		{
			mechanismReader >> axisReversibility;
		}
		else
		if(tempName1 == "axis_rotation") 
		{
			mechanismReader >> axisRotation;
		}
		else
		if(tempName1 == "crank_eccentricity")
		{
			mechanismReader >> crankEccentricity;
		}
		else
		if(tempName1 == "rod_length")
		{
			mechanismReader >> rodLength;
		}
		else
		if(tempName1 == "stroke")
		{
			mechanismReader >> mechanismStroke;
		}
	}
}

string Input::getMechanismDisplacement()
{
	return mechanismDisplacement;
}

double Input::getAxisReversibility()
{
	return axisReversibility;
}

double Input::getAxisRotation()
{
	return axisRotation;
}

double Input::getCrankEccentricity()
{
	return crankEccentricity;
}

double Input::getRodLength()
{
	return rodLength;
}

double Input::getMechanismStroke()
{
	return mechanismStroke;
}

void Input::readCompressionSystemData()
{
	ifstream compSystemReader;

	compSystemReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(compSystemReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(compSystemReader , comment);
		}
		else
		if(tempName1 == "cylinder")
		{
			compSystemReader >> cylinderShape;
		}
		else
		if(tempName1 == "cylinder_bore")
		{
			compSystemReader >> cylinderBore;
		}
		else
		if(tempName1 == "cylinder_deadvolume")
		{
			compSystemReader >> cylinderDeadVolume;
		}
		else
		if(tempName1 == "cylinder_length")
		{
			compSystemReader >> cylinderLength;
		}
		else
		if(tempName1 == "cylinder_coniclength")
		{
			compSystemReader >> cylinderConicLength;
		}
		else
		if(tempName1 == "cylinder_axisdistance")
		{
			compSystemReader >> cylinderAxisDistance;
		}
		else
		if(tempName1 == "piston_headlength")
		{
			compSystemReader >> pistonHeadLength;
		}
		else
		if(tempName1 == "piston_skirtlength")
		{
			compSystemReader >> pistonSkirtLength;
		}		
	}
}

string Input::getCylinderShape()
{
	return cylinderShape;
}

double Input::getCylinderBore()
{
	return cylinderBore;
}

double Input::getCylinderDeadVolume()
{
	return cylinderDeadVolume;
}

double Input::getCylinderLength()
{
	return cylinderLength;
}

double Input::getCylinderConicLength()
{
	return cylinderConicLength;
}

double Input::getCylinderAxisDistance()
{
	return cylinderAxisDistance;
}

double Input::getPistonHeadLength()
{
	return pistonHeadLength;
}

double Input::getPistonSkirtLength()
{
	return pistonSkirtLength;
}


void Input::readLeakData()
{
	ifstream leakReader;

	leakReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(leakReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( leakReader , comment);
		}
		else
		if(tempName1 == "gap")
		{
			leakReader >> leakGap;
		}
		else
		if(tempName1 == "gap_inferiordeadpoint")
		{
			leakReader >> leakInfDeadPointGap;
		}
		else
		if(tempName1 == "seal")
		{
			leakReader >> leakSeal;
		}
		else
		if(tempName1 == "shell_pressure")
		{
			leakReader >> leakShellPressure;
		}
	}
}

double Input::getLeakGap()
{
	return leakGap;
}

double Input::getLeakInfDeadPointGap()
{
	return leakInfDeadPointGap;
}

double Input::getLeakShellPressure()
{
	return leakShellPressure*1.0E0;
}

string Input::getLeakSeal()
{
	return leakSeal;
}

void Input::readAnnulusLeakData()
{
	ifstream annulusLeakReader;

	annulusLeakReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(annulusLeakReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( annulusLeakReader , comment);
		}
		else
		if(tempName1 == "annulus")
		{
			annulusLeakReader >> annulusLeakDirection;
		}

		if(annulusLeakDirection == "suction")
		{
			if(tempName1 == "min_area")
			{
				annulusLeakReader >> annulusLeakSucMinArea;
			}
			else
			if(tempName1 == "max_area")
			{
				annulusLeakReader >> annulusLeakSucMaxArea;
			}
			else
			if(tempName1 == "delta_pressure")
			{
				annulusLeakReader >> annulusLeakSucDeltaPressure;
			}
			else
			if(tempName1 == "correction_coeficient")
			{
				annulusLeakReader >> annulusLeakSucCorrecCoef;
			}	
		}
		else
		if(annulusLeakDirection == "discharge")
		{
			if(tempName1 == "min_area")
			{
				annulusLeakReader >> annulusLeakDisMinArea;
			}
			else
			if(tempName1 == "max_area")
			{
				annulusLeakReader >> annulusLeakDisMaxArea;
			}
			else
			if(tempName1 == "delta_pressure")
			{
				annulusLeakReader >> annulusLeakDisDeltaPressure;
			}
			else
			if(tempName1 == "correction_coeficient")
			{
				annulusLeakReader >> annulusLeakDisCorrecCoef;
			}	
		}
	}
}

double Input::getAnnulusLeakSucMaxArea()
{
	return annulusLeakSucMaxArea;
}

double Input::getAnnulusLeakSucMinArea()
{
	return annulusLeakSucMinArea;
}

double Input::getAnnulusLeakSucDeltaPressure()
{
	return annulusLeakSucDeltaPressure;
}

double Input::getAnnulusLeakSucCorrecCoef()
{
	return annulusLeakSucCorrecCoef;
}

double Input::getAnnulusLeakDisMaxArea()
{
	return annulusLeakDisMaxArea;
}

double Input::getAnnulusLeakDisMinArea()
{
	return annulusLeakDisMinArea;
}

double Input::getAnnulusLeakDisDeltaPressure()
{
	return annulusLeakDisDeltaPressure;
}
double Input::getAnnulusLeakDisCorrecCoef()
{
	return annulusLeakDisCorrecCoef;
}

void Input::readOrificeData()
{
	ifstream orificeReader;

	orificeReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;

	while(orificeReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( orificeReader , comment);
		}
		else
		if(tempName1 == "Orifice")
		{
			orificeReader >> tempValue1;

			setOrificeId(tempValue1);
		}
		else
		if(tempName1 == "direction")
		{
			orificeReader >> orificeDirection[orificeId];
		}
	}

	orificeReader.close();
}

void Input::contOrificesNumber()
{
	ifstream orificeReader;

	orificeReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;

	while(orificeReader >> tempName1)
	{
		if( tempName1 == "Orifice")
		{
			++orificesNumber;
		}
	}
	orificeReader.close();
}

void Input::dimensionOrificeVector()
{
	orificeDirection.resize(orificesNumber,"empty");
}

void Input::setOrificeId(double orificeIdValue)
{
	orificeId = orificeIdValue;
}

int Input::getOrificesNumber()
{
	return orificesNumber;
}

string Input::getOrificeDirection(int id)
{
	return orificeDirection[id];
}

void Input::dimensionEffectFlowAreaVector()
{
	effectFlowAreaPointsNumber.resize(orificesNumber,0);

	backflowEffectFlowAreaPointsNumber.resize(orificesNumber,0);
}

void Input::contEffectFlowAreaPointsNumber()
{
	ifstream effectAreaReader;

	effectAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	double tempValue2 = 0;
	double tempValue3 = 0;
	string tempName1;
	string tempName2;

	while(effectAreaReader >> tempName1)
	{
		if( tempName1 == "Orifice")
		{
			effectAreaReader >> tempValue1;
		}

		if( tempName1 == "direction")
		{
			tempValue2 = 0;
			tempValue3 = 0;

			while(effectAreaReader >> tempName2 && tempName2 != "end")
			{
				if(tempName2 == "effectiveflowarea")
				{
					tempValue2++;
				}

				if(tempName2 == "effectivebackflowarea")
				{
					tempValue3++;
				}
			}

			effectFlowAreaPointsNumber[tempValue1] = tempValue2;
			backflowEffectFlowAreaPointsNumber[tempValue1] = tempValue3;
		}
	}

	effectAreaReader.close();
}

void Input::dimensionEffectFlowAreaMatrix()
{
	maxNumberEffectFlowAreaPoints = 0;
	maxNumberBackFlowEffectFlowAreaPoints = 0;

	for(int i = 0; i < effectFlowAreaPointsNumber.size(); i++)
	{
		if(effectFlowAreaPointsNumber[i] >= maxNumberEffectFlowAreaPoints)
		{
			maxNumberEffectFlowAreaPoints = effectFlowAreaPointsNumber[i];
		}
	}

	for(int i = 0; i < backflowEffectFlowAreaPointsNumber.size(); i++)
	{
		if(backflowEffectFlowAreaPointsNumber[i] >= maxNumberBackFlowEffectFlowAreaPoints)
		{
			maxNumberBackFlowEffectFlowAreaPoints = backflowEffectFlowAreaPointsNumber[i];
		}
	}

	vector<double> vectorTemp1;
	vector<double> vectorTemp2;

	vectorTemp1.resize(maxNumberEffectFlowAreaPoints, 0);
	vectorTemp2.resize(maxNumberBackFlowEffectFlowAreaPoints, 0);

	effectFlowArea.resize(orificesNumber,vectorTemp1);
	effectBackflowArea.resize(orificesNumber,vectorTemp2);

	valveDisplacement.resize(orificesNumber,vectorTemp1);
}

void Input::readEffectFlowArea()
{
	ifstream effectiveFlowAreaReader;

	effectiveFlowAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;
	int i = 0;
	int j = 0;
	int y = 0;

	while(effectiveFlowAreaReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(effectiveFlowAreaReader , comment);
		}
		else
		if(tempName1 == "Orifice")
		{
			effectiveFlowAreaReader >> tempValue1;
			setOrificeId(tempValue1);
			i = 0;
			j = 0;
			y = 0;
		}
		else
		if(tempName1 == "effectiveflowarea")
		{
			effectiveFlowAreaReader >> effectFlowArea[orificeId][i]; 	
			++i;
		}
		else
		if(tempName1 == "effectivebackflowarea")
		{
			effectiveFlowAreaReader >> effectBackflowArea[orificeId][j]; 	
			++j;

		}
		else
		if(tempName1 == "valvedisplacement")
		{
			effectiveFlowAreaReader >> valveDisplacement[orificeId][y]; 	
			++y;
		}
	}		
}

vector<double> Input::getEffectFlowAreaData(int id)
{	
	vector<double> effectFlowAreaDataTemp;

	for(int i = 0; i < maxNumberEffectFlowAreaPoints; i++)
	{
		effectFlowAreaDataTemp.push_back(effectFlowArea[id][i]);
	}

	return effectFlowAreaDataTemp;
}

vector<double> Input::getEffectiveBackFlowAreaData(int id)
{
	vector<double> effectBackflowAreaDataTemp;

	for(int i = 0; i < maxNumberBackFlowEffectFlowAreaPoints; i++)
	{
		effectBackflowAreaDataTemp.push_back(effectBackflowArea[id][i]);
	}

	return effectBackflowAreaDataTemp;
}

vector<double> Input::getValveDisplacementData(int id)
{
	vector<double> valveDisplacementDataTemp;

	for(int i = 0; i < maxNumberEffectFlowAreaPoints; i++)
	{
		valveDisplacementDataTemp.push_back(valveDisplacement[id][i]);
	}

	return valveDisplacementDataTemp;
}

void Input::dimensionEffectForceAreaVector()
{
	effectForceAreaPointsNumber.resize(orificesNumber,0);

	backflowEffectForceAreaPointsNumber.resize(orificesNumber,0);
}

void Input::contEffectForceAreaPointsNumber()
{
	ifstream effectAreaReader;

	effectAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	double tempValue2 = 0;
	double tempValue3 = 0;
	string tempName1;
	string tempName2;

	while(effectAreaReader >> tempName1)
	{
		if(tempName1 == "Orifice")
		{
			effectAreaReader >> tempValue1;
		}

		if( tempName1 == "direction")
		{
			tempValue2 = 0;
			tempValue3 = 0;

			while(effectAreaReader >> tempName2 && tempName2 != "end")
			{
				if(tempName2 == "effectiveforcearea")
				{
					tempValue2++;
				}

				if(tempName2 == "backfloweffectiveforcearea")
				{
					tempValue3++;
				}
			}

			effectForceAreaPointsNumber[tempValue1] = tempValue2;
			backflowEffectForceAreaPointsNumber[tempValue1] = tempValue3;
		}
	}

	effectAreaReader.close();
}

void Input::dimensionEffectForceAreaMatrix()
{
	maxNumberEffectForceAreaPoints = 0;
	maxNumberBackFlowEffectForceAreaPoints = 0;

	for(int i = 0; i < effectForceAreaPointsNumber.size(); i++)
	{
		if(effectForceAreaPointsNumber[i] >= maxNumberEffectForceAreaPoints)
		{
			maxNumberEffectForceAreaPoints = effectForceAreaPointsNumber[i];
		}
	}

	for(int i = 0; i < backflowEffectForceAreaPointsNumber.size(); i++)
	{
		if(backflowEffectForceAreaPointsNumber[i] >= maxNumberBackFlowEffectForceAreaPoints)
		{
			maxNumberBackFlowEffectForceAreaPoints = backflowEffectForceAreaPointsNumber[i];
		}
	}

	vector<double> vectorTemp1;
	vector<double> vectorTemp2;

	vectorTemp1.resize(maxNumberEffectForceAreaPoints, 0);
	vectorTemp2.resize(maxNumberBackFlowEffectForceAreaPoints, 0);

	effectForceArea.resize(orificesNumber,vectorTemp1);
	backflowEffectForceArea.resize(orificesNumber,vectorTemp2);

	effectForceAreaValveDisplacement.resize(orificesNumber,vectorTemp1);
}

void Input::readEffectForceArea()
{
	ifstream effectiveForceAreaReader;

	effectiveForceAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;
	int i = 0;
	int j = 0;
	int y = 0;

	
	while(effectiveForceAreaReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(effectiveForceAreaReader , comment);
		}
		
		else
		if(tempName1 == "Orifice")
		{
			effectiveForceAreaReader >> tempValue1;
			setOrificeId(tempValue1);
			i = 0;
			j = 0;
			y = 0;
		}
		else
		if(tempName1 == "effectiveforcearea")
		{
			effectiveForceAreaReader >> effectForceArea[orificeId][i]; 	
			++i;
		}
		else
		if(tempName1 == "backfloweffectiveforcearea")
		{
			effectiveForceAreaReader >> backflowEffectForceArea[orificeId][j]; 	
			++j;
		}
		else
		if(tempName1 == "valvedisplacement")
		{
			effectiveForceAreaReader >> effectForceAreaValveDisplacement[orificeId][y]; 	
			++y;
		}
	}
}

vector<double> Input::getEffectForceAreaData(int id)
{	
	vector<double> effectForceAreaDataTemp;

	for(int i = 0; i < maxNumberEffectForceAreaPoints; i++)
	{
		effectForceAreaDataTemp.push_back(effectForceArea[id][i]);
	}

	return effectForceAreaDataTemp;
}

vector<double> Input::getBackFlowEffectiveForceAreaData(int id)
{
	vector<double> backflowEffectForceAreaDataTemp;

	for(int i = 0; i < maxNumberBackFlowEffectForceAreaPoints; i++)
	{
		backflowEffectForceAreaDataTemp.push_back(backflowEffectForceArea[id][i]);
	}

	return backflowEffectForceAreaDataTemp;
}

vector<double> Input::getEffectForceAreaValveDisplacementData(int id)
{
	vector<double> valveDisplacementDataTemp;

	for(int i = 0; i < maxNumberEffectForceAreaPoints; i++)
	{
		valveDisplacementDataTemp.push_back(effectForceAreaValveDisplacement[id][i]);
	}

	return valveDisplacementDataTemp;
}

void Input::dimensionDynamicSystemVector()
{
	stickingForce.resize(orificesNumber,0);
	impellerHeight.resize(orificesNumber,0);
	impellerPreTension.resize(orificesNumber,0);
	valveNatFrequency.resize(orificesNumber,0);
	valveStiffness.resize(orificesNumber,0);
	valveDamping.resize(orificesNumber,0);
	valvePreTension.resize(orificesNumber,0);
	boosterHeight.resize(orificesNumber,0);
	stopperHeight.resize(orificesNumber,0);
	dynSystNatFrequency.resize(orificesNumber,0);
	dynSystStiffness.resize(orificesNumber,0);
}

void Input::readDynamicSystemData()
{
	ifstream dynamicSystemReader;

	dynamicSystemReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;

	while(dynamicSystemReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(dynamicSystemReader, comment);
		}
		else
		if(tempName1 == "Orifice")
		{
			dynamicSystemReader >> tempValue1;

			setOrificeId(tempValue1);
		}
		else
		if(tempName1 == "sticking_force")
		{
			dynamicSystemReader >> stickingForce[orificeId];
		}
		else
		if(tempName1 == "impeller_height")
		{
			dynamicSystemReader >> impellerHeight[orificeId];
		}
		else
		if(tempName1 == "impeller_pretension")
		{
			dynamicSystemReader >> impellerPreTension[orificeId];
		}
		else
		if(tempName1 == "valve_natfrequency")
		{
			dynamicSystemReader >> valveNatFrequency[orificeId];
		}
		else
		if(tempName1 == "valve_stiffness")
		{
			dynamicSystemReader >> valveStiffness[orificeId];
		}
		else
		if(tempName1 == "valve_damping")
		{
			dynamicSystemReader >> valveDamping[orificeId];
		}
		else
		if(tempName1 == "valve_pretension")
		{
			dynamicSystemReader >> valvePreTension[orificeId];
		}
		else
		if(tempName1 == "booster_height")
		{
			dynamicSystemReader >> boosterHeight[orificeId];
		}
		else
		if(tempName1 == "stopper_height")
		{
			dynamicSystemReader >> stopperHeight[orificeId];
		}
		else
		if(tempName1 == "natfrequency")
		{
			dynamicSystemReader >> dynSystNatFrequency[orificeId];
		}
		else
		if(tempName1 == "stiffness")
		{
			dynamicSystemReader >> dynSystStiffness[orificeId];
		}
	}
}

double Input::getStickingForce(int id)
{
	return stickingForce[id];
}

double Input::getImpellerHeight(int id)
{
	return impellerHeight[id];
}

double Input::getImpellerPreTension(int id)
{
	return impellerPreTension[id];
}

double Input::getValveNatFrequency(int id)
{
	return valveNatFrequency[id];
}

double Input::getValveStiffness(int id)
{
	return valveStiffness[id];
}

double Input::getValveDamping(int id)
{
	return valveDamping[id];
}

double Input::getValvePreTension(int id)
{
	return valvePreTension[id];
}

double Input::getBoosterHeight(int id)
{
	return boosterHeight[id];
}

double Input::getStopperHeight(int id)
{
	return stopperHeight[id];
}

double Input::getDynSystNatFrequency(int id)
{
	return dynSystNatFrequency[id];
}

double Input::getDynSystStiffness(int id)
{
	return dynSystStiffness[id];
}

void Input::readSimulationParametersData()
{
	ifstream simulParamReader;

	simulParamReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(simulParamReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( simulParamReader , comment);
		}
		else
		if(tempName1 == "delta_theta")
		{
			simulParamReader >> simulParamDeltaTheta;
		}
		else
		if(tempName1 == "cycles_number")
		{
			simulParamReader >> simulParamCyclesNumber;
		}
		else
		if(tempName1 == "pertubation")
		{
			simulParamReader >> simulParamPertubation;
		}	
		if(tempName1 == "flag_thermal_balance")
		{
			simulParamReader >> simulParamThermalBalanceFlag;
		}
		
		if(tempName1 == "flag_thermal_simulation")
		{
			simulParamReader >> simulParamThermalSimulationFlag;
		}
		
		if(tempName1 == "direct_suction_factor")
		{
			simulParamReader >> simulParamDirectSuctionFactor;
		}
	}

	simulParamReader.close();
}

double Input::getSimulParamDeltaTheta()
{
	return simulParamDeltaTheta;
}

double Input::getSimulParamCyclesNumber()
{
	return simulParamCyclesNumber;
}

double Input::getSimulParamPertubation()
{
	return simulParamPertubation;
}

double Input::getSimulParamThermalBalanceFlag()
{
	return simulParamThermalBalanceFlag;
}

double Input::getSimulParamThermalSimulationFlag()
{
	return simulParamThermalSimulationFlag;
}

double Input::getSimulParamDirectSuctionFactor()
{
	return simulParamDirectSuctionFactor;
}

void Input::readExpTempData()
{
	ifstream expTempReader;

	expTempReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(expTempReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( expTempReader , comment);
		}
		else
		if(tempName1 == "evaporation")
		{
			expTempReader >> expTempEvaporation;
		}

		if(tempName1 == "condesation")
		{
			expTempReader >> expTempCondesation;
		}

		if(tempName1 == "subcooling")
		{
			expTempReader >> expTempSubcooling;
		}

		if(tempName1 == "superheating")
		{
			expTempReader >> expTempSuperheating;
		}

		if(tempName1 == "suction_line")
		{
			expTempReader >> expTempSuctionLine;
		}

		if(tempName1 == "discharge_line")
		{
			expTempReader >> expTempDischargeLine;
		}

		if(tempName1 == "suction_chamber")
		{
			expTempReader >> expTempSuctionChamber;
		}

		if(tempName1 == "discharge_chamber")
		{
			expTempReader >> expTempDischargeChamber;
		}

		if(tempName1 == "cylinder_wall")
		{
			expTempReader >> expTempCylinderWall;
		}

		if(tempName1 == "bearings")
		{
			expTempReader >> expTempBearings;
		}

		if(tempName1 == "oil")
		{
			expTempReader >> expTempOil;
		}

		if(tempName1 == "motor")
		{
			expTempReader >> expTempMotor;
		}
		if(tempName1 == "shell")
		{
			expTempReader >> expTempShell;
		}
		if(tempName1 == "external_environment")
		{
			expTempReader >> expTempExternalEnvironment;
		}
		if(tempName1 == "internal_environment")
		{
			expTempReader >> expTempInternalEnvironment;
		}
		if(tempName1 == "discharge_muffler")
		{
			expTempReader >> expTempDischargeMuffler;
		}
	}

	expTempReader.close();
}

double Input::getExpTempEvaporation()
{
	return (expTempEvaporation + 273.15);
}

double Input::getExpTempCondesation()
{
	return (expTempCondesation+ 273.15);
}

double Input::getExpTempSubcooling()
{
	return (expTempSubcooling+ 273.15);
}

double Input::getExpTempSuperheating()
{
	return (expTempSuperheating + 273.15);
}

double Input::getExpTempSuctionLine()
{
	return (expTempSuctionLine + 273.15);
}

double Input::getExpTempDischargeLine()
{
	return (expTempDischargeLine + 273.15);
}

double Input::getExpTempSuctionChamber()
{
	return (expTempSuctionChamber + 273.15);
}

double Input::getExpTempDischargeChamber()
{
	return (expTempDischargeChamber + 273.15);
}

double Input::getExpTempCylinderWall()
{
	return (expTempCylinderWall + 273.15);
}

double Input::getExpTempBearings()
{
	return (expTempBearings + 273.15);
}

double Input::getExpTempOil()
{
	return (expTempOil + 273.15);
}

double Input::getExpTempMotor()
{
	return (expTempMotor + 273.15);
}

double Input::getExpTempDischargeMuffler()
{
	return (expTempDischargeMuffler + 273.15);
}

double Input::getExpTempExternalEnvironment()
{
	return (expTempExternalEnvironment + 273.15);
}

double Input::getExpTempInternalEnvironment()
{
	return (expTempInternalEnvironment + 273.15);
}

double Input::getExpTempShell()
{
	return (expTempShell + 273.15);
}

void Input::readOilData()
{
	ifstream oilReader;

	oilReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(oilReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( oilReader , comment);
		}
		else
		if(tempName1 == "viscosisity_coef_1")
		{
			oilReader >> oilViscosityCoef1;
		}

		if(tempName1 == "viscosisity_coef_2")
		{
			oilReader >> oilViscosityCoef2;
		}

		if(tempName1 == "viscosisity_coef_3")
		{
			oilReader >> oilViscosityCoef3;
		}
	}

	oilReader.close();
}

double Input::getOilViscosityCoef1()
{
	return oilViscosityCoef1;
}

double Input::getOilViscosityCoef2()
{
	return oilViscosityCoef2;
}

double Input::getOilViscosityCoef3()
{
	return oilViscosityCoef3;
}

void Input::readBearingsData()
{
	ifstream bearingsReader;

	bearingsReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(bearingsReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( bearingsReader , comment);
		}
		else
		if(tempName1 == "loses")
		{
			bearingsReader >> bearingsLoses;
		}

		if(tempName1 == "avaliation_temperature")
		{
			bearingsReader >> bearingsAvaliationTemp;
		}
	}

	bearingsReader.close();
}

double Input::getBearingsLoses()
{
	return bearingsLoses;
}

double Input::getBearingsAvaliationTemperature()
{
	return bearingsAvaliationTemp + 273.15;
}

void Input::contMotorCoefNumber()
{
	ifstream motorReader;

	motorReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;

	while(motorReader >> tempName1)
	{
		if( tempName1 == "coef")
		{
			++motorCoefNumber;
		}
	}
	motorReader.close();
}

void Input::dimensionMotorCoef()
{
	motorCoef.resize(motorCoefNumber, 0);
}

void Input::readMotorData()
{
	ifstream motorReader;

	motorReader.open("input.dat", ios::in);

	string tempName1;

	double tempValue1;

	double tempValue2;

	string comment;

	while(motorReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( motorReader , comment);
		}
		else
		if(tempName1 == "coef")
		{
			motorReader >> tempValue1;

			motorReader >> tempValue2;

			motorCoef[tempValue1 - 1] = tempValue2; 
		}
	}
}

int Input::getMotorCoefNumber()
{
	return motorCoefNumber;
}

vector<double> Input::getMotorCoef()
{
	return motorCoef;
}







/*



#include "Input.h"

Input::Input()
{
	mechanismDisplacement = "crank_rod";
	axisReversibility = 0;
	mechanismStroke = 0;
	cylinderDeadVolume = 0;
	cylinderLength = 0;
	cylinderConicLength = 0;
	leakShellPressure = -1;
	leakSeal = "absent";
	orificesNumber = 0;
	motorCoefNumber = 0;
}

void Input::readRefrigerantData()
{
	ifstream refrigerantReader;

	refrigerantReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(refrigerantReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(refrigerantReader, comment);
		}
		else
		if(tempName1 == "refrigerant")
		{
			refrigerantReader >> refrigerantName;
		}
		else
		if(tempName1 == "viscosity_thermalcond")
		{
			refrigerantReader >> refrigViscosityThermalCondCalc;
		}	
	}
}

string Input::getRefrigViscThermalCondCalc()
{
	return refrigViscosityThermalCondCalc;
}

void Input::readMechanismData()
{
	ifstream mechanismReader;

	mechanismReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(mechanismReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(mechanismReader , comment);
		}
		else
		if(tempName1 == "mechanism_displacement") 
		{
			mechanismReader >> mechanismDisplacement;
		}
		else
		if(tempName1 == "axis_reversibility")
		{
			mechanismReader >> axisReversibility;
		}
		else
		if(tempName1 == "axis_rotation") 
		{
			mechanismReader >> axisRotation;
		}
		else
		if(tempName1 == "crank_eccentricity")
		{
			mechanismReader >> crankEccentricity;
		}
		else
		if(tempName1 == "rod_length")
		{
			mechanismReader >> rodLength;
		}
		else
		if(tempName1 == "stroke")
		{
			mechanismReader >> mechanismStroke;
		}
	}
}

string Input::getMechanismDisplacement()
{
	return mechanismDisplacement;
}

double Input::getAxisReversibility()
{
	return axisReversibility;
}

double Input::getAxisRotation()
{
	return axisRotation;
}

double Input::getCrankEccentricity()
{
	return crankEccentricity;
}

double Input::getRodLength()
{
	return rodLength;
}

double Input::getMechanismStroke()
{
	return mechanismStroke;
}

void Input::readCompressionSystemData()
{
	ifstream compSystemReader;

	compSystemReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(compSystemReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(compSystemReader , comment);
		}
		else
		if(tempName1 == "cylinder")
		{
			compSystemReader >> cylinderShape;
		}
		else
		if(tempName1 == "cylinder_bore")
		{
			compSystemReader >> cylinderBore;
		}
		else
		if(tempName1 == "cylinder_deadvolume")
		{
			compSystemReader >> cylinderDeadVolume;
		}
		else
		if(tempName1 == "cylinder_length")
		{
			compSystemReader >> cylinderLength;
		}
		else
		if(tempName1 == "cylinder_coniclength")
		{
			compSystemReader >> cylinderConicLength;
		}
		else
		if(tempName1 == "cylinder_axisdistance")
		{
			compSystemReader >> cylinderAxisDistance;
		}
		else
		if(tempName1 == "piston_headlength")
		{
			compSystemReader >> pistonHeadLength;
		}
		else
		if(tempName1 == "piston_skirtlength")
		{
			compSystemReader >> pistonSkirtLength;
		}		
	}
}

string Input::getCylinderShape()
{
	return cylinderShape;
}

double Input::getCylinderBore()
{
	return cylinderBore;
}

double Input::getCylinderDeadVolume()
{
	return cylinderDeadVolume;
}

double Input::getCylinderLength()
{
	return cylinderLength;
}

double Input::getCylinderConicLength()
{
	return cylinderConicLength;
}

double Input::getCylinderAxisDistance()
{
	return cylinderAxisDistance;
}

double Input::getPistonHeadLength()
{
	return pistonHeadLength;
}

double Input::getPistonSkirtLength()
{
	return pistonSkirtLength;
}

void Input::readLeakData()
{
	ifstream leakReader;

	leakReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(leakReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( leakReader , comment);
		}
		else
		if(tempName1 == "gap")
		{
			leakReader >> leakGap;
		}
		else
		if(tempName1 == "gap_inferiordeadpoint")
		{
			leakReader >> leakInfDeadPointGap;
		}
		else
		if(tempName1 == "seal")
		{
			leakReader >> leakSeal;
		}
		else
		if(tempName1 == "shell_pressure")
		{
			leakReader >> leakShellPressure;
		}
	}
}

double Input::getLeakGap()
{
	return leakGap;
}

double Input::getLeakInfDeadPointGap()
{
	return leakInfDeadPointGap;
}

double Input::getLeakShellPressure()
{
	return leakShellPressure*1.0E0;
}

string Input::getLeakSeal()
{
	return leakSeal;
}

void Input::readAnnulusLeakData()
{
	ifstream annulusLeakReader;

	annulusLeakReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(annulusLeakReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( annulusLeakReader , comment);
		}
		else
		if(tempName1 == "annulus")
		{
			annulusLeakReader >> annulusLeakDirection;
		}

		if(annulusLeakDirection == "suction")
		{
			if(tempName1 == "min_area")
			{
				annulusLeakReader >> annulusLeakSucMinArea;
			}
			else
			if(tempName1 == "max_area")
			{
				annulusLeakReader >> annulusLeakSucMaxArea;
			}
			else
			if(tempName1 == "delta_pressure")
			{
				annulusLeakReader >> annulusLeakSucDeltaPressure;
			}
			else
			if(tempName1 == "correction_coeficient")
			{
				annulusLeakReader >> annulusLeakSucCorrecCoef;
			}	
		}
		else
		if(annulusLeakDirection == "discharge")
		{
			if(tempName1 == "min_area")
			{
				annulusLeakReader >> annulusLeakDisMinArea;
			}
			else
			if(tempName1 == "max_area")
			{
				annulusLeakReader >> annulusLeakDisMaxArea;
			}
			else
			if(tempName1 == "delta_pressure")
			{
				annulusLeakReader >> annulusLeakDisDeltaPressure;
			}
			else
			if(tempName1 == "correction_coeficient")
			{
				annulusLeakReader >> annulusLeakDisCorrecCoef;
			}	
		}
	}
}

double Input::getAnnulusLeakSucMaxArea()
{
	return annulusLeakSucMaxArea;
}

double Input::getAnnulusLeakSucMinArea()
{
	return annulusLeakSucMinArea;
}

double Input::getAnnulusLeakSucDeltaPressure()
{
	return annulusLeakSucDeltaPressure;
}

double Input::getAnnulusLeakSucCorrecCoef()
{
	return annulusLeakSucCorrecCoef;
}

double Input::getAnnulusLeakDisMaxArea()
{
	return annulusLeakDisMaxArea;
}

double Input::getAnnulusLeakDisMinArea()
{
	return annulusLeakDisMinArea;
}

double Input::getAnnulusLeakDisDeltaPressure()
{
	return annulusLeakDisDeltaPressure;
}
double Input::getAnnulusLeakDisCorrecCoef()
{
	return annulusLeakDisCorrecCoef;
}

void Input::readOrificeData()
{
	ifstream orificeReader;

	orificeReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;

	while(orificeReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( orificeReader , comment);
		}
		else
		if(tempName1 == "Orifice")
		{
			orificeReader >> tempValue1;

			setOrificeId(tempValue1);
		}
		else
		if(tempName1 == "direction")
		{
			orificeReader >> orificeDirection[orificeId];
		}
	}

	orificeReader.close();
}

void Input::contOrificesNumber()
{
	ifstream orificeReader;

	orificeReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;

	while(orificeReader >> tempName1)
	{
		if( tempName1 == "Orifice")
		{
			++orificesNumber;
		}
	}
	orificeReader.close();
}

void Input::dimensionOrificeVector()
{
	orificeDirection.resize(orificesNumber,"empty");
}

void Input::setOrificeId(double orificeIdValue)
{
	orificeId = orificeIdValue;
}

double Input::getOrificesNumber()
{
	return orificesNumber;
}

string Input::getOrificeDirection(int id)
{
	return orificeDirection[id];
}

void Input::dimensionEffectFlowAreaVector()
{
	effectFlowAreaPointsNumber.resize(orificesNumber,0);

	backflowEffectFlowAreaPointsNumber.resize(orificesNumber,0);
}

void Input::contEffectFlowAreaPointsNumber()
{
	ifstream effectAreaReader;

	effectAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	double tempValue2 = 0;
	double tempValue3 = 0;
	string tempName1;
	string tempName2;

	while(effectAreaReader >> tempName1)
	{
		if( tempName1 == "Orifice")
		{
			effectAreaReader >> tempValue1;
		}

		if( tempName1 == "direction")
		{
			tempValue2 = 0;
			tempValue3 = 0;

			while(effectAreaReader >> tempName2 && tempName2 != "end")
			{
				if(tempName2 == "effectiveflowarea")
				{
					tempValue2++;
				}

				if(tempName2 == "effectivebackflowarea")
				{
					tempValue3++;
				}
			}

			effectFlowAreaPointsNumber[tempValue1] = tempValue2;
			backflowEffectFlowAreaPointsNumber[tempValue1] = tempValue3;
		}
	}

	effectAreaReader.close();
}

void Input::dimensionEffectFlowAreaMatrix()
{
	maxNumberEffectFlowAreaPoints = 0;
	maxNumberBackFlowEffectFlowAreaPoints = 0;

	for(int i = 0; i < effectFlowAreaPointsNumber.size(); i++)
	{
		if(effectFlowAreaPointsNumber[i] >= maxNumberEffectFlowAreaPoints)
		{
			maxNumberEffectFlowAreaPoints = effectFlowAreaPointsNumber[i];
		}
	}

	for(int i = 0; i < backflowEffectFlowAreaPointsNumber.size(); i++)
	{
		if(backflowEffectFlowAreaPointsNumber[i] >= maxNumberBackFlowEffectFlowAreaPoints)
		{
			maxNumberBackFlowEffectFlowAreaPoints = backflowEffectFlowAreaPointsNumber[i];
		}
	}

	vector<double> vectorTemp1;
	vector<double> vectorTemp2;

	vectorTemp1.resize(maxNumberEffectFlowAreaPoints, 0);
	vectorTemp2.resize(maxNumberBackFlowEffectFlowAreaPoints, 0);

	effectFlowArea.resize(orificesNumber,vectorTemp1);
	effectBackflowArea.resize(orificesNumber,vectorTemp2);

	valveDisplacement.resize(orificesNumber,vectorTemp1);
}

void Input::readEffectFlowArea()
{
	ifstream effectiveFlowAreaReader;

	effectiveFlowAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;
	int i = 0;
	int j = 0;
	int y = 0;

	while(effectiveFlowAreaReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(effectiveFlowAreaReader , comment);
		}
		else
		if(tempName1 == "Orifice")
		{
			effectiveFlowAreaReader >> tempValue1;
			setOrificeId(tempValue1);
			i = 0;
			j = 0;
			y = 0;
		}
		else
		if(tempName1 == "effectiveflowarea")
		{
			effectiveFlowAreaReader >> effectFlowArea[orificeId][i]; 	
			++i;
		}
		else
		if(tempName1 == "effectivebackflowarea")
		{
			effectiveFlowAreaReader >> effectBackflowArea[orificeId][j]; 	
			++j;

		}
		else
		if(tempName1 == "valvedisplacement")
		{
			effectiveFlowAreaReader >> valveDisplacement[orificeId][y]; 	
			++y;
		}
	}		
}

vector<double> Input::getEffectFlowAreaData(int id)
{	
	vector<double> effectFlowAreaDataTemp;

	for(int i = 0; i < maxNumberEffectFlowAreaPoints; i++)
	{
		effectFlowAreaDataTemp.push_back(effectFlowArea[id][i]);
	}

	return effectFlowAreaDataTemp;
}

vector<double> Input::getEffectiveBackFlowAreaData(int id)
{
	vector<double> effectBackflowAreaDataTemp;

	for(int i = 0; i < maxNumberBackFlowEffectFlowAreaPoints; i++)
	{
		effectBackflowAreaDataTemp.push_back(effectBackflowArea[id][i]);
	}

	return effectBackflowAreaDataTemp;
}

vector<double> Input::getValveDisplacementData(int id)
{
	vector<double> valveDisplacementDataTemp;

	for(int i = 0; i < maxNumberEffectFlowAreaPoints; i++)
	{
		valveDisplacementDataTemp.push_back(valveDisplacement[id][i]);
	}

	return valveDisplacementDataTemp;
}

void Input::dimensionEffectForceAreaVector()
{
	effectForceAreaPointsNumber.resize(orificesNumber,0);

	backflowEffectForceAreaPointsNumber.resize(orificesNumber,0);
}

void Input::contEffectForceAreaPointsNumber()
{
	ifstream effectAreaReader;

	effectAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	double tempValue2 = 0;
	double tempValue3 = 0;
	string tempName1;
	string tempName2;

	while(effectAreaReader >> tempName1)
	{
		if(tempName1 == "Orifice")
		{
			effectAreaReader >> tempValue1;
		}

		if( tempName1 == "direction")
		{
			tempValue2 = 0;
			tempValue3 = 0;

			while(effectAreaReader >> tempName2 && tempName2 != "end")
			{
				if(tempName2 == "effectiveforcearea")
				{
					tempValue2++;
				}

				if(tempName2 == "backfloweffectiveforcearea")
				{
					tempValue3++;
				}
			}

			effectForceAreaPointsNumber[tempValue1] = tempValue2;
			backflowEffectForceAreaPointsNumber[tempValue1] = tempValue3;
		}
	}

	effectAreaReader.close();
}

void Input::dimensionEffectForceAreaMatrix()
{
	maxNumberEffectForceAreaPoints = 0;
	maxNumberBackFlowEffectForceAreaPoints = 0;

	for(int i = 0; i < effectForceAreaPointsNumber.size(); i++)
	{
		if(effectForceAreaPointsNumber[i] >= maxNumberEffectForceAreaPoints)
		{
			maxNumberEffectForceAreaPoints = effectForceAreaPointsNumber[i];
		}
	}

	for(int i = 0; i < backflowEffectForceAreaPointsNumber.size(); i++)
	{
		if(backflowEffectForceAreaPointsNumber[i] >= maxNumberBackFlowEffectForceAreaPoints)
		{
			maxNumberBackFlowEffectForceAreaPoints = backflowEffectForceAreaPointsNumber[i];
		}
	}

	vector<double> vectorTemp1;
	vector<double> vectorTemp2;

	vectorTemp1.resize(maxNumberEffectForceAreaPoints, 0);
	vectorTemp2.resize(maxNumberBackFlowEffectForceAreaPoints, 0);

	effectForceArea.resize(orificesNumber,vectorTemp1);
	backflowEffectForceArea.resize(orificesNumber,vectorTemp2);

	valveDisplacement.resize(orificesNumber,vectorTemp1);
}

void Input::readEffectForceArea()
{
	ifstream effectiveForceAreaReader;

	effectiveForceAreaReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;
	int i = 0;
	int j = 0;
	int y = 0;

	while(effectiveForceAreaReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(effectiveForceAreaReader , comment);
		}
		else
		if(tempName1 == "Orifice")
		{
			effectiveForceAreaReader >> tempValue1;
			setOrificeId(tempValue1);
			i = 0;
			j = 0;
			y = 0;
		}
		else
		if(tempName1 == "effectiveforcearea")
		{
			effectiveForceAreaReader >> effectForceArea[orificeId][i]; 	
			++i;
		}
		else
		if(tempName1 == "backfloweffectiveforcearea")
		{
			effectiveForceAreaReader >> backflowEffectForceArea[orificeId][j]; 	
			++j;
		}
		if(tempName1 == "valvedisplacement")
		{
			effectiveForceAreaReader >> valveDisplacement[orificeId][y]; 	
			++y;
		}
	}		
}

vector<double> Input::getEffectForceAreaData(int id)
{	
	vector<double> effectForceAreaDataTemp;

	for(int i = 0; i < maxNumberEffectForceAreaPoints; i++)
	{
		effectForceAreaDataTemp.push_back(effectForceArea[id][i]);
	}

	return effectForceAreaDataTemp;
}

vector<double> Input::getBackFlowEffectiveForceAreaData(int id)
{
	vector<double> backflowEffectForceAreaDataTemp;

	for(int i = 0; i < maxNumberBackFlowEffectForceAreaPoints; i++)
	{
		backflowEffectForceAreaDataTemp.push_back(backflowEffectForceArea[id][i]);
	}

	return backflowEffectForceAreaDataTemp;
}

vector<double> Input::getEffectForceAreaValveDisplacementData(int id)
{
	vector<double> valveDisplacementDataTemp;

	for(int i = 0; i < maxNumberEffectForceAreaPoints; i++)
	{
		valveDisplacementDataTemp.push_back(valveDisplacement[id][i]);
	}

	return valveDisplacementDataTemp;
}

void Input::dimensionDynamicSystemVector()
{
	stickingForce.resize(orificesNumber,0);
	impellerHeight.resize(orificesNumber,0);
	impellerPreTension.resize(orificesNumber,0);
	valveNatFrequency.resize(orificesNumber,0);
	valveStiffness.resize(orificesNumber,0);
	valveDamping.resize(orificesNumber,0);
	valvePreTension.resize(orificesNumber,0);
	boosterHeight.resize(orificesNumber,0);
	stopperHeight.resize(orificesNumber,0);
	dynSystNatFrequency.resize(orificesNumber,0);
	dynSystStiffness.resize(orificesNumber,0);
}

void Input::readDynamicSystemData()
{
	ifstream dynamicSystemReader;

	dynamicSystemReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;
	string comment;

	while(dynamicSystemReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline(dynamicSystemReader, comment);
		}
		else
		if(tempName1 == "Orifice")
		{
			dynamicSystemReader >> tempValue1;

			setOrificeId(tempValue1);
		}
		else
		if(tempName1 == "sticking_force")
		{
			dynamicSystemReader >> stickingForce[orificeId];
		}
		else
		if(tempName1 == "impeller_height")
		{
			dynamicSystemReader >> impellerHeight[orificeId];
		}
		else
		if(tempName1 == "impeller_pretension")
		{
			dynamicSystemReader >> impellerPreTension[orificeId];
		}
		else
		if(tempName1 == "valve_natfrequency")
		{
			dynamicSystemReader >> valveNatFrequency[orificeId];
		}
		else
		if(tempName1 == "valve_stiffness")
		{
			dynamicSystemReader >> valveStiffness[orificeId];
		}
		else
		if(tempName1 == "valve_damping")
		{
			dynamicSystemReader >> valveDamping[orificeId];
		}
		else
		if(tempName1 == "valve_pretension")
		{
			dynamicSystemReader >> valvePreTension[orificeId];
		}
		else
		if(tempName1 == "booster_height")
		{
			dynamicSystemReader >> boosterHeight[orificeId];
		}
		else
		if(tempName1 == "stopper_height")
		{
			dynamicSystemReader >> stopperHeight[orificeId];
		}
		else
		if(tempName1 == "natfrequency")
		{
			dynamicSystemReader >> dynSystNatFrequency[orificeId];
		}
		else
		if(tempName1 == "stiffness")
		{
			dynamicSystemReader >> dynSystStiffness[orificeId];
		}
	}
}

double Input::getStickingForce(int id)
{
	return stickingForce[id];
}

double Input::getImpellerHeight(int id)
{
	return impellerHeight[id];
}

double Input::getImpellerPreTension(int id)
{
	return impellerPreTension[id];
}

double Input::getValveNatFrequency(int id)
{
	return valveNatFrequency[id];
}

double Input::getValveStiffness(int id)
{
	return valveStiffness[id];
}

double Input::getValveDamping(int id)
{
	return valveDamping[id];
}

double Input::getValvePreTension(int id)
{
	return valvePreTension[id];
}

double Input::getBoosterHeight(int id)
{
	return boosterHeight[id];
}

double Input::getStopperHeight(int id)
{
	return stopperHeight[id];
}

double Input::getDynSystNatFrequency(int id)
{
	return dynSystNatFrequency[id];
}

double Input::getDynSystStiffness(int id)
{
	return dynSystStiffness[id];
}

void Input::readSimulationParametersData()
{
	ifstream simulParamReader;

	simulParamReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(simulParamReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( simulParamReader , comment);
		}
		else
		if(tempName1 == "delta_theta")
		{
			simulParamReader >> simulParamDeltaTheta;
		}

		if(tempName1 == "cycles_number")
		{
			simulParamReader >> simulParamCyclesNumber;
		}		
	}

	simulParamReader.close();
}

double Input::getSimulParamDeltaTheta()
{
	return simulParamDeltaTheta;
}

double Input::getSimulParamCyclesNumber()
{
	return simulParamCyclesNumber;
}

void Input::readExpTempData()
{
	ifstream expTempReader;

	expTempReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(expTempReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( expTempReader , comment);
		}
		else
		if(tempName1 == "evaporation")
		{
			expTempReader >> expTempEvaporation;
		}

		if(tempName1 == "condesation")
		{
			expTempReader >> expTempCondesation;
		}

		if(tempName1 == "subcooling")
		{
			expTempReader >> expTempSubcooling;
		}

		if(tempName1 == "superheating")
		{
			expTempReader >> expTempSuperheating;
		}

		if(tempName1 == "suction_line")
		{
			expTempReader >> expTempSuctionLine;
		}

		if(tempName1 == "discharge_line")
		{
			expTempReader >> expTempDischargeLine;
		}

		if(tempName1 == "suction_chamber")
		{
			expTempReader >> expTempSuctionChamber;
		}

		if(tempName1 == "discharge_chamber")
		{
			expTempReader >> expTempDischargeChamber;
		}

		if(tempName1 == "cylinder_wall")
		{
			expTempReader >> expTempCylinderWall;
		}

		if(tempName1 == "bearings")
		{
			expTempReader >> expTempBearings;
		}

		if(tempName1 == "oil")
		{
			expTempReader >> expTempOil;
		}

		if(tempName1 == "motor")
		{
			expTempReader >> expTempMotor;
		}
	}

	expTempReader.close();
}

double Input::getExpTempEvaporation()
{
	return (expTempEvaporation + 273.15);
}

double Input::getExpTempCondesation()
{
	return (expTempCondesation+ 273.15);
}

double Input::getExpTempSubcooling()
{
	return (expTempSubcooling+ 273.15);
}

double Input::getExpTempSuperheating()
{
	return (expTempSuperheating + 273.15);
}

double Input::getExpTempSuctionLine()
{
	return (expTempSuctionLine + 273.15);
}

double Input::getExpTempDischargeLine()
{
	return (expTempDischargeLine + 273.15);
}

double Input::getExpTempSuctionChamber()
{
	return (expTempSuctionChamber + 273.15);
}

double Input::getExpTempDischargeChamber()
{
	return (expTempDischargeChamber + 273.15);
}

double Input::getExpTempCylinderWall()
{
	return (expTempCylinderWall + 273.15);
}

double Input::getExpTempBearings()
{
	return (expTempBearings + 273.15);
}

double Input::getExpTempOil()
{
	return (expTempOil + 273.15);
}

double Input::getExpTempMotor()
{
	return (expTempMotor + 273.15);
}

void Input::readOilData()
{
	ifstream oilReader;

	oilReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(oilReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( oilReader , comment);
		}
		else
		if(tempName1 == "viscosisity_coef_1")
		{
			oilReader >> oilViscosityCoef1;
		}

		if(tempName1 == "viscosisity_coef_2")
		{
			oilReader >> oilViscosityCoef2;
		}

		if(tempName1 == "viscosisity_coef_3")
		{
			oilReader >> oilViscosityCoef3;
		}
	}

	oilReader.close();
}

double Input::getOilViscosityCoef1()
{
	return oilViscosityCoef1;
}

double Input::getOilViscosityCoef2()
{
	return oilViscosityCoef2;
}

double Input::getOilViscosityCoef3()
{
	return oilViscosityCoef3;
}

void Input::readBearingsData()
{
	ifstream bearingsReader;

	bearingsReader.open("input.dat", ios::in);

	string tempName1;

	string comment;

	while(bearingsReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( bearingsReader , comment);
		}
		else
		if(tempName1 == "loses")
		{
			bearingsReader >> bearingsLoses;
		}

		if(tempName1 == "avaliation_temperature")
		{
			bearingsReader >> bearingsAvaliationTemp;
		}
	}

	bearingsReader.close();
}

double Input::getBearingsLoses()
{
	return bearingsLoses;
}

double Input::getBearingsAvaliationTemperature()
{
	return bearingsAvaliationTemp + 273.15;
}

void Input::contMotorCoefNumber()
{
	ifstream motorReader;

	motorReader.open("input.dat", ios::in);

	double tempValue1 = 0;
	string tempName1;

	while(motorReader >> tempName1)
	{
		if( tempName1 == "coef")
		{
			++motorCoefNumber;
		}
	}
	motorReader.close();
}

void Input::dimensionMotorCoef()
{
	motorCoef.resize(motorCoefNumber, 0);
}

void Input::readMotorData()
{
	ifstream motorReader;

	motorReader.open("input.dat", ios::in);

	string tempName1;

	double tempValue1;

	double tempValue2;

	string comment;

	while(motorReader >> tempName1)
	{
		if(tempName1 == "//")
		{
			getline( motorReader , comment);
		}
		else
		if(tempName1 == "coef")
		{
			motorReader >> tempValue1;

			motorReader >> tempValue2;

			motorCoef[tempValue1 - 1] = tempValue2; 
		}
	}
}

int Input::getMotorCoefNumber()
{
	return motorCoefNumber;
}

vector<double> Input::getMotorCoef()
{
	return motorCoef;
}

*/









