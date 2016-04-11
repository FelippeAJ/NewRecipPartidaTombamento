#include "OrificesSet.h"

OrificesSet::OrificesSet()
{
	Input orificesSetReaderData;

	orificesSetReaderData.contOrificesNumber();

	setNumber(orificesSetReaderData.getOrificesNumber());

	totalSucMassFlow = 0;
	totalSucFlux = 0;
	totalSucBackflow = 0;
	totalDisMassFlow = 0;
	totalDisFlux = 0;
	totalDisBackflow = 0;

	
}

void OrificesSet::calcSpecificHeatsRatioMedia(double sucChamberSpecificHeatsRatio, double disChamberSpecificHeatsRatio)
{
	specificHeatsRatioMedia = (sucChamberSpecificHeatsRatio + disChamberSpecificHeatsRatio)/2;
}

void OrificesSet::calcCriticPress()
{
	criticPress = pow((2.0/(specificHeatsRatioMedia + 1.0)),(specificHeatsRatioMedia/(specificHeatsRatioMedia - 1.0)));
}

void OrificesSet::calcUpstreamTemp(double cylTemp, double sucChamberTemp, double disChamberTemp, double cylPress, double sucChamberPress, double disChamberPress)
{
	if(sucChamberPress > cylPress)
	{
		sucUpstreamTemp = sucChamberTemp;
	}
	else
	{
		sucUpstreamTemp = cylTemp;
	}

	if(cylPress > disChamberPress)
	{
		disUpstreamTemp = cylTemp;
	}
	else
	{
		disUpstreamTemp = disChamberTemp;
	}
}

void OrificesSet::calcUpstreamPress(double cylPress, double sucChamberPress, double disChamberPress)
{
	sucUpstreamPress = max(cylPress, sucChamberPress);

	disUpstreamPress = max(cylPress,disChamberPress);
}

void OrificesSet:: calcPressRatio(double cylPress, double sucChamberPress, double disChamberPress)
{
	if(cylPress <= sucChamberPress)
	{
		sucPressRatio = max((cylPress/sucChamberPress),criticPress);
	}
	else
	{
		sucPressRatio = max((sucChamberPress/cylPress),criticPress);
	}

	if(cylPress <= disChamberPress)
	{
		disPressRatio = max((cylPress/disChamberPress),criticPress);
	}
	else
	{
		disPressRatio = max((disChamberPress/cylPress),criticPress);
	}
}

void OrificesSet::calcTotalSucMassFlow(double sucMassFlow)
{
	totalSucMassFlow += sucMassFlow;
}

void OrificesSet::calcTotalSucFlux(double sucFlux)
{
	totalSucFlux += sucFlux;
}

void OrificesSet::calcTotalSucBackflow(double sucBackflow)
{
	totalSucBackflow +=  sucBackflow;
}

void OrificesSet::calcTotalDisMassFlow(double disMassFlow)
{
	totalDisMassFlow += disMassFlow;
}

void OrificesSet::calcTotalDisFlux(double disFlux)
{
	totalDisFlux += disFlux;
}

void OrificesSet::calcTotalDisBackflow(double disBackflow)
{
	totalDisBackflow += disBackflow;
}

void OrificesSet::setNumber(double numberValue)
{
	number = numberValue;
}

void OrificesSet::setTotalSucMassFlow(double totalSucMassFlowValue)
{
	totalSucMassFlow = totalSucMassFlowValue;
}

void OrificesSet::setTotalSucFlux(double totalSucFluxValue)
{
	totalSucFlux = totalSucFluxValue;
}

void OrificesSet::setTotalSucBackflow(double totalSucBackflowValue)
{
	totalSucBackflow = totalSucBackflowValue;
}

void OrificesSet::setTotalDisMassFlow(double totalDisMassFlowValue)
{
	totalDisMassFlow = totalDisMassFlowValue;
}

void OrificesSet::setTotalDisFlux(double totalDisFluxValue)
{
	totalDisFlux = totalDisFluxValue;
}

void OrificesSet::setTotalDisBackflow(double totalDisBackflowValue)
{
	totalDisBackflow = totalDisBackflowValue;
}

double OrificesSet::getNumber()
{
	return number;
}

double OrificesSet::getSpecificHeatsRatioMedia()
{
	return specificHeatsRatioMedia;
}

double OrificesSet::getCriticPress()
{
	return criticPress;
}

double OrificesSet::getSucUpstreamTemp()
{
	return sucUpstreamTemp;
}

double OrificesSet::getSucUpstreamPress()
{
	return sucUpstreamPress;
}

double OrificesSet::getSucPressRatio()
{
	return sucPressRatio;
}

double OrificesSet::getTotalSucMassFlow()
{
	return totalSucMassFlow;
}

double OrificesSet::getTotalSucFlux()
{
	return totalSucFlux;
}

double OrificesSet::getTotalSucBackflow()
{
	return totalSucBackflow;
}

double OrificesSet::getDisUpstreamTemp()
{
	return disUpstreamTemp;
}

double OrificesSet::getDisUpstreamPress()
{
	return disUpstreamPress;
}

double OrificesSet::getDisPressRatio()
{
	return disPressRatio;
}

double OrificesSet::getTotalDisMassFlow()
{
	return totalDisMassFlow;
}

double OrificesSet::getTotalDisFlux()
{
	return totalDisFlux;
}

double OrificesSet::getTotalDisBackflow()
{
	return totalDisBackflow;
}
