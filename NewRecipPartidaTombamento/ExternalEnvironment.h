#ifndef EXTERNALENVIRONMENT_H
#define EXTERNALENVIRONMENT_H

#include "Input.h"
#include "Refrigerant.h"
#include "GlobalHeatTransfer.h"
#include "HeatTransferRate.h"

class ExternalEnvironment
{
public:
	ExternalEnvironment();
		
	Refrigerant refrigerant;
	GlobalHeatTransfer UAobj;
	HeatTransferRate heatTransferRateObj;

protected:

};

#endif