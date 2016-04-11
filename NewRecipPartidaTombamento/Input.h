#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Input
{
public:
	Input();
	~Input();

	void readRefrigerantData();
	char refrigerantName[24];
	string getRefrigViscThermalCondCalc();
	
	void readMechanismData();
	string getMechanismDisplacement();
	double getMechanismStroke();
	double getAxisReversibility();
	double getAxisRotation();
	double getCrankEccentricity();
	double getRodLength();

	void readCompressionSystemData();
	string getCylinderShape();
	double getCylinderBore();
	double getCylinderDeadVolume();
	double getCylinderLength();
	double getCylinderConicLength();
	double getCylinderAxisDistance();
	double getPistonHeadLength();
	double getPistonSkirtLength();

	void readLeakData();
	double getLeakGap();
	double getLeakInfDeadPointGap();
	double getLeakShellPressure();
	string getLeakSeal();

	void readAnnulusLeakData();
	double getAnnulusLeakDirection();
	double getAnnulusLeakSucMinArea();
	double getAnnulusLeakSucMaxArea();
	double getAnnulusLeakSucDeltaPressure();
	double getAnnulusLeakSucCorrecCoef();
	double getAnnulusLeakDisMinArea();
	double getAnnulusLeakDisMaxArea();
	double getAnnulusLeakDisDeltaPressure();
	double getAnnulusLeakDisCorrecCoef();

	void readOrificeData();
	void contOrificesNumber();
	void dimensionOrificeVector();
	void setOrificeId(double orificeIdValue);
	int getOrificesNumber();
	string getOrificeDirection(int id);

	void readEffectFlowArea();
	void dimensionEffectFlowAreaVector();
	void contEffectFlowAreaPointsNumber();
	void dimensionEffectFlowAreaMatrix();
	vector<double> getEffectFlowAreaData(int id);
	vector<double> getEffectiveBackFlowAreaData(int id);
	vector<double> getValveDisplacementData(int id);
	

	void readEffectForceArea();
	void dimensionEffectForceAreaVector();
	void contEffectForceAreaPointsNumber();
	void dimensionEffectForceAreaMatrix();
	vector<double> getEffectForceAreaData(int id);
	vector<double> getBackFlowEffectiveForceAreaData(int id);
	vector<double> getEffectForceAreaValveDisplacementData(int id);

	void readDynamicSystemData();
	void dimensionDynamicSystemVector();
	double getStickingForce(int id);
	double getImpellerHeight(int id);
	double getImpellerPreTension(int id);
	double getValveNatFrequency(int id);
	double getValveStiffness(int id);
	double getValveDamping(int id);
	double getValvePreTension(int id);
	double getBoosterHeight(int id);
	double getStopperHeight(int id);
	double getDynSystNatFrequency(int id);
	double getDynSystStiffness(int id);

	void readSimulationParametersData();
	double getSimulParamDeltaTheta();
	double getSimulParamCyclesNumber();
	double getSimulParamPertubation();
	double getSimulParamThermalBalanceFlag();
	double getSimulParamThermalSimulationFlag();
	double getSimulParamDirectSuctionFactor();

	void readExpTempData();
	double getExpTempEvaporation();
	double getExpTempCondesation();
	double getExpTempSubcooling();
	double getExpTempSuperheating();
	double getExpTempSuctionLine();
	double getExpTempDischargeLine();
	double getExpTempSuctionChamber();
	double getExpTempDischargeChamber();
	double getExpTempCylinderWall();
	double getExpTempBearings();
	double getExpTempOil();
	double getExpTempMotor();
	double getExpTempInternalEnvironment();
	double getExpTempDischargeMuffler();
	double getExpTempShell();
	double getExpTempExternalEnvironment();

	void readOilData();
	double getOilViscosityCoef1();
	double getOilViscosityCoef2();
	double getOilViscosityCoef3();

	void readBearingsData();
	double getBearingsLoses();
	double getBearingsAvaliationTemperature();

	void readMotorData();				
	void contMotorCoefNumber();			
	void dimensionMotorCoef();			
	vector<double> getMotorCoef();		
	int getMotorCoefNumber();			

	void readPostProcData();
	double getPostProcCycle();
	double getPostProcFrequency();

protected:
	string refrigViscosityThermalCondCalc;

	string mechanismDisplacement;
	double axisReversibility;
	double axisRotation;
	double crankEccentricity;
	double rodLength;
	double mechanismStroke;

	string cylinderShape;
	double cylinderBore;
	double cylinderDeadVolume;
	double cylinderLength;
	double cylinderConicLength;
	double cylinderAxisDistance;
	double pistonHeadLength;
	double pistonSkirtLength;

	double leakGap;
	double leakInfDeadPointGap;
	double leakShellPressure;
	string leakSeal;

	string annulusLeakDirection;
	double annulusLeakSucMinArea;
	double annulusLeakSucMaxArea;
	double annulusLeakSucDeltaPressure;
	double annulusLeakSucCorrecCoef;
	double annulusLeakDisMinArea;
	double annulusLeakDisMaxArea;
	double annulusLeakDisDeltaPressure;
	double annulusLeakDisCorrecCoef;

	int orificesNumber;
	int orificeId;
	vector<string> orificeDirection;

	vector<vector<double>> effectFlowArea;
	vector<vector<double>> effectBackflowArea;
	vector<vector<double>> valveDisplacement;
	vector<int> effectFlowAreaPointsNumber;
	vector<int> backflowEffectFlowAreaPointsNumber;
	int maxNumberEffectFlowAreaPoints;
	int maxNumberBackFlowEffectFlowAreaPoints;

	vector<vector<double>> effectForceArea;
	vector<vector<double>> backflowEffectForceArea;
	vector<vector<double>> effectForceAreaValveDisplacement;
	vector<int> effectForceAreaPointsNumber;
	vector<int> backflowEffectForceAreaPointsNumber;
	int maxNumberEffectForceAreaPoints;
	int maxNumberBackFlowEffectForceAreaPoints;

	vector<double> stickingForce;
	vector<double> impellerHeight;
	vector<double> impellerPreTension;
	vector<double> valveNatFrequency;
	vector<double> valveStiffness;
	vector<double> valveDamping;
	vector<double> valvePreTension;
	vector<double> boosterHeight;
	vector<double> stopperHeight;
	vector<double> dynSystNatFrequency;
	vector<double> dynSystStiffness;

	double simulParamDeltaTheta;
	double simulParamCyclesNumber;
	double simulParamPertubation;
	double simulParamThermalBalanceFlag;
	double simulParamThermalSimulationFlag;
	double simulParamDirectSuctionFactor;

	double expTempEvaporation;
	double expTempCondesation;
	double expTempSubcooling;
	double expTempSuperheating;
	double expTempSuctionLine;
	double expTempDischargeLine;
	double expTempSuctionChamber;
	double expTempDischargeChamber;
	double expTempCylinderWall;
	double expTempBearings;
	double expTempOil;
	double expTempMotor;
	double expTempInternalEnvironment;
	double expTempDischargeMuffler;
	double expTempShell;
	double expTempExternalEnvironment;

	

	double oilViscosityCoef1;
	double oilViscosityCoef2;
	double oilViscosityCoef3;

	double bearingsLoses;
	double bearingsAvaliationTemp;

	int motorCoefNumber;
	vector<double> motorCoef;

	double postProcCycle();
	double postProcFrequency();

	
};

#endif




/*



#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Input
{
public:
	Input();

	void readRefrigerantData();
	char refrigerantName[24];
	string getRefrigViscThermalCondCalc();
	
	void readMechanismData();
	string getMechanismDisplacement();
	double getMechanismStroke();
	double getAxisReversibility();
	double getAxisRotation();
	double getCrankEccentricity();
	double getRodLength();

	void readCompressionSystemData();
	string getCylinderShape();
	double getCylinderBore();
	double getCylinderDeadVolume();
	double getCylinderLength();
	double getCylinderConicLength();
	double getCylinderAxisDistance();
	double getPistonHeadLength();
	double getPistonSkirtLength();

	void readLeakData();
	double getLeakGap();
	double getLeakInfDeadPointGap();
	double getLeakShellPressure();
	string getLeakSeal();

	void readAnnulusLeakData();
	double getAnnulusLeakDirection();
	double getAnnulusLeakSucMinArea();
	double getAnnulusLeakSucMaxArea();
	double getAnnulusLeakSucDeltaPressure();
	double getAnnulusLeakSucCorrecCoef();
	double getAnnulusLeakDisMinArea();
	double getAnnulusLeakDisMaxArea();
	double getAnnulusLeakDisDeltaPressure();
	double getAnnulusLeakDisCorrecCoef();

	void readOrificeData();
	void contOrificesNumber();
	void dimensionOrificeVector();
	void setOrificeId(double orificeIdValue);
	double getOrificesNumber();
	string getOrificeDirection(int id);

	void readEffectFlowArea();
	void dimensionEffectFlowAreaVector();
	void contEffectFlowAreaPointsNumber();
	void dimensionEffectFlowAreaMatrix();
	vector<double> getEffectFlowAreaData(int id);
	vector<double> getEffectiveBackFlowAreaData(int id);
	vector<double> getValveDisplacementData(int id);

	void readEffectForceArea();
	void dimensionEffectForceAreaVector();
	void contEffectForceAreaPointsNumber();
	void dimensionEffectForceAreaMatrix();
	vector<double> getEffectForceAreaData(int id);
	vector<double> getBackFlowEffectiveForceAreaData(int id);
	vector<double> getEffectForceAreaValveDisplacementData(int id);

	void readDynamicSystemData();
	void dimensionDynamicSystemVector();
	double getStickingForce(int id);
	double getImpellerHeight(int id);
	double getImpellerPreTension(int id);
	double getValveNatFrequency(int id);
	double getValveStiffness(int id);
	double getValveDamping(int id);
	double getValvePreTension(int id);
	double getBoosterHeight(int id);
	double getStopperHeight(int id);
	double getDynSystNatFrequency(int id);
	double getDynSystStiffness(int id);

	void readSimulationParametersData();
	double getSimulParamDeltaTheta();
	double getSimulParamCyclesNumber();

	void readExpTempData();
	double getExpTempEvaporation();
	double getExpTempCondesation();
	double getExpTempSubcooling();
	double getExpTempSuperheating();
	double getExpTempSuctionLine();
	double getExpTempDischargeLine();
	double getExpTempSuctionChamber();
	double getExpTempDischargeChamber();
	double getExpTempCylinderWall();
	double getExpTempBearings();
	double getExpTempOil();
	double getExpTempMotor();

	void readOilData();
	double getOilViscosityCoef1();
	double getOilViscosityCoef2();
	double getOilViscosityCoef3();

	void readBearingsData();
	double getBearingsLoses();
	double getBearingsAvaliationTemperature();

	void readMotorData();				
	void contMotorCoefNumber();			
	void dimensionMotorCoef();			
	vector<double> getMotorCoef();		
	int getMotorCoefNumber();			

	void readPostProcData();
	double getPostProcCycle();
	double getPostProcFrequency();

protected:
	string refrigViscosityThermalCondCalc;

	string mechanismDisplacement;
	double axisReversibility;
	double axisRotation;
	double crankEccentricity;
	double rodLength;
	double mechanismStroke;

	string cylinderShape;
	double cylinderBore;
	double cylinderDeadVolume;
	double cylinderLength;
	double cylinderConicLength;
	double cylinderAxisDistance;
	double pistonHeadLength;
	double pistonSkirtLength;

	double leakGap;
	double leakInfDeadPointGap;
	double leakShellPressure;
	string leakSeal;

	string annulusLeakDirection;
	double annulusLeakSucMinArea;
	double annulusLeakSucMaxArea;
	double annulusLeakSucDeltaPressure;
	double annulusLeakSucCorrecCoef;
	double annulusLeakDisMinArea;
	double annulusLeakDisMaxArea;
	double annulusLeakDisDeltaPressure;
	double annulusLeakDisCorrecCoef;

	int orificesNumber;
	int orificeId;
	vector<string> orificeDirection;

	vector<vector<double>> effectFlowArea;
	vector<vector<double>> effectBackflowArea;
	vector<vector<double>> valveDisplacement;
	vector<int> effectFlowAreaPointsNumber;
	vector<int> backflowEffectFlowAreaPointsNumber;
	int maxNumberEffectFlowAreaPoints;
	int maxNumberBackFlowEffectFlowAreaPoints;
	
	vector<vector<double>> effectForceArea;
	vector<vector<double>> backflowEffectForceArea;
	vector<int> effectForceAreaPointsNumber;
	vector<int> backflowEffectForceAreaPointsNumber;
	int maxNumberEffectForceAreaPoints;
	int maxNumberBackFlowEffectForceAreaPoints;

	vector<double> stickingForce;
	vector<double> impellerHeight;
	vector<double> impellerPreTension;
	vector<double> valveNatFrequency;
	vector<double> valveStiffness;
	vector<double> valveDamping;
	vector<double> valvePreTension;
	vector<double> boosterHeight;
	vector<double> stopperHeight;
	vector<double> dynSystNatFrequency;
	vector<double> dynSystStiffness;

	double simulParamDeltaTheta;
	double simulParamCyclesNumber;

	double expTempEvaporation;
	double expTempCondesation;
	double expTempSubcooling;
	double expTempSuperheating;
	double expTempSuctionLine;
	double expTempDischargeLine;
	double expTempSuctionChamber;
	double expTempDischargeChamber;
	double expTempCylinderWall;
	double expTempBearings;
	double expTempOil;
	double expTempMotor;

	double oilViscosityCoef1;
	double oilViscosityCoef2;
	double oilViscosityCoef3;

	double bearingsLoses;
	double bearingsAvaliationTemp;

	int motorCoefNumber;
	vector<double> motorCoef;

	double postProcCycle();
	double postProcFrequency();

	
};

#endif

*/

