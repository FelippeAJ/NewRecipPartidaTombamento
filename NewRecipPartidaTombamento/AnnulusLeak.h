#ifndef ANNULUSLEAK
#define ANNULUSLEAK

#include "Input.h"
#include <cmath>

class AnnulusLeak
{
public:
	AnnulusLeak();

	void calcSucArea(double cylPress, double sucChamberPress);
	void calcDisArea(double cylPress, double disChamberPress);
//	void calcSucMassFlow(double cylPress, double sucChamberPress, double cylRho, double orificesNumber ,DynamicSystemFactory dynSystemFact);
//	void calcDisMassFlow(double cylPress, double disChamberPress, double disChamberRho, double orificesNumber ,DynamicSystemFactory dynSystemFact);

	void setSucMaxArea(double sucMaxAreaValue);
	void setSucMinArea(double sucMinAreaValue);
	void setSucDeltaPressure(double sucDeltaPressureValue);
	void setSucCorrectionCoef(double sucCorrectCoefValue);

	void setDisMaxArea(double disMaxAreaValue);
	void setDisMinArea(double disMinAreaValue);
	void setDisDeltaPressure(double disDeltaPressureValue);
	void setDisCorrectionCoef(double disCorrectCoefValue);

	double getSucMassFlow();
	double getDisMassFlow();

protected:
	double sucMaxArea;
	double sucMinArea;
	double sucDeltaPressure;
	double sucCorrectionCoeficient;
	double disMaxArea;
	double disMinArea;
	double disDeltaPressure;
	double disCorrectionCoeficient;
	double sucArea;
	double disArea;
	double sucMassFlow;
	double disMassFlow;
};

#endif