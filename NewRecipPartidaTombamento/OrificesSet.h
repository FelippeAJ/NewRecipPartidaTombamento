#ifndef ORIFICESSET_H 
#define ORIFICESSET_H

#include "Input.h"
#include "OrificeFactory.h"

class OrificesSet
{
public:
	OrificesSet();

	void calcSpecificHeatsRatioMedia(double sucChamberSpecificHeatsRatio, double disChamberSpecificHeatsRatio);
	void calcCriticPress();
	void calcUpstreamTemp(double cylTemp, double sucChamberTemp, double disChamberTemp, double cylPress, double sucChamberPress, double disChamberPress);
	void calcUpstreamPress(double cylPress, double sucChamberPress, double disChamberPress);
	void calcPressRatio(double cylPress, double sucChamberPress, double disChamberPress);
	void calcTotalSucMassFlow(double sucMassFlow);
	void calcTotalSucFlux(double sucFlux);
	void calcTotalSucBackflow(double sucBackflow);
	void calcTotalDisMassFlow(double disMassFlow);
	void calcTotalDisFlux(double disFlux);
	void calcTotalDisBackflow(double disBackflow);

	void setNumber(double numberValue);
	void setTotalSucMassFlow(double totalSucMassFlowValue);
	void setTotalSucFlux(double totalSucFluxValue);
	void setTotalSucBackflow(double totalSucBackflowValue);
	void setTotalDisMassFlow(double totalDisMassFlowValue);
	void setTotalDisFlux(double totalDisFluxValue);
	void setTotalDisBackflow(double totalDisBackflowValue);

	double getNumber();
	double getSpecificHeatsRatioMedia();
	double getCriticPress();
	double getSucUpstreamTemp();
	double getSucUpstreamPress();
	double getSucPressRatio();
	double getTotalSucMassFlow();
	double getTotalSucFlux();
	double getTotalSucBackflow();
	double getDisUpstreamTemp();
	double getDisUpstreamPress();
	double getDisPressRatio();
	double getTotalDisMassFlow();
	double getTotalDisFlux();
	double getTotalDisBackflow();

	OrificeFactory orificeFact;

protected:
	double number;
	double specificHeatsRatioMedia;
	double criticPress;
	double sucUpstreamTemp;
	double sucUpstreamPress;
	double sucPressRatio;
	double totalSucMassFlow;
	double totalSucFlux;
	double totalSucBackflow;
	double disUpstreamTemp;
	double disUpstreamPress;
	double disPressRatio;
	double totalDisMassFlow;
	double totalDisFlux;
	double totalDisBackflow;
};

#endif


