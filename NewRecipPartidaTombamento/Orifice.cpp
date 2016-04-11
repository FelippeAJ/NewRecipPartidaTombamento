#include "Orifice.h"

int Orifice::id = 0;

Orifice::Orifice()
{
	POLOIO POLOIOobj1("input.dat");
	string idStr = to_string(id);

	direction		=	POLOIOobj1.getWord("orifice", idStr, "direction", "left");


	POLOIO POLOIOobj2("AEE.dat");
	
	effFlAreaObj.setPointNum(POLOIOobj2.getParamVal("orifice", idStr, "points_number", "left"));
	effFlAreaObj.setValveDisp(POLOIOobj2.getColumnMatrix("orifice_data_matrix", idStr, "right", effFlAreaObj.getPointNum() , 0));
	effFlAreaObj.setEffFlArea(POLOIOobj2.getColumnMatrix("orifice_data_matrix", idStr, "right", effFlAreaObj.getPointNum() , 1));
	effFlAreaObj.setBackfEffFlArea(POLOIOobj2.getColumnMatrix("orifice_data_matrix", idStr, "right", effFlAreaObj.getPointNum() , 2));

	incremId();

	massFl			=	0;
	fl				=	0;
	backf			=	0;
	massSumFl		=	0;
	enSumFl			=	0;
	massSumBackf	=	0;
	totSucMassFl	=	0;
	totSucFl		=	0;
	totSucBackf		=	0;
	totDisMassFl	=	0;
	totDisFl		=	0;
	totDisBackf		=	0;
	
}

void Orifice::calcSucMassFl()
{
	double A = 2*specHeatRatMed/((specHeatRatMed -1)*refrig.getGasCt()*sucUpTemp);

	double B = pow(sucPressRat,(2/specHeatRatMed)) - pow(sucPressRat,(specHeatRatMed + 1)/specHeatRatMed);

	massFl = effFlAreaObj.getSucEffFlArea() * sucUpPress*sqrt(A)*sqrt(B);
}

void Orifice::calcDisMassFl()
{
	double A = 2*specHeatRatMed/((specHeatRatMed -1)*refrig.getGasCt()*disUpTemp);

	double B = pow(disPressRat,(2/specHeatRatMed)) - pow(disPressRat,(specHeatRatMed + 1)/specHeatRatMed);

	massFl = effFlAreaObj.getDisEfftFlArea()*disUpPress*sqrt(A)*sqrt(B);
}

void Orifice::calcFl()
{
	if(massFl >= 0)
	{
		fl = massFl;
		backf = 0;
	}
	else
	{
		fl = 0;
		backf = -massFl;
	}
}

void Orifice::calcMassSum(double timeStep)
{
	if(massFl > 0)
	{
		massSumFl += massFl*timeStep;
	}
	else
	{
		massSumBackf = massSumBackf - massFl*timeStep;
	}
}


void Orifice::setMassFl(double massFlVal)
{
	massFl = massFlVal;
}

double Orifice::getMassFl()
{
	return massFl;
}

double Orifice::getFl()
{
	return fl;
}

double Orifice::getBackf()
{
	return backf;
}

double Orifice::getMassSumFl()
{
	return massSumFl;
}

double Orifice::getMassSumBackf()
{
	return massSumBackf;
}

void Orifice::incremId()
{
	++id;
}

void Orifice::calcSpecHeatRatMed(double sucChambSpecHeatRat, double disChambSpecHeatRat)
{
	specHeatRatMed = (sucChambSpecHeatRat + disChambSpecHeatRat)/2;
}

void Orifice::calcCritPress()
{
	critPress = pow((2.0/(specHeatRatMed + 1.0)),(specHeatRatMed/(specHeatRatMed - 1.0)));
}

void Orifice::calcSucUpTemp(double compChambTemp, double sucChambTemp, double compChambPress, double sucChambPress)
{
	if(sucChambPress > compChambPress)
	{
		sucUpTemp = sucChambTemp;
	}
	else
	{
		sucUpTemp = compChambTemp;
	}
}

void Orifice::calcDisUpTemp(double compChambTemp, double disChambTemp, double compChambPress, double disChambPress)
{
	if(compChambPress > disChambPress)
	{
		disUpTemp = compChambTemp;
	}
	else
	{
		disUpTemp = disChambTemp;
	}
}

void Orifice::calcSucUpPress(double compChambPress, double sucChambPress)
{
	sucUpPress = max(compChambPress, sucChambPress);
}

void Orifice::calcDisUpPress(double compChambPress, double disChambPress)
{
	disUpPress = max(compChambPress,disChambPress);
}

void Orifice::calcSucPressRat(double compChambPress, double sucChambPress)
{
	if(compChambPress <= sucChambPress)
	{
		sucPressRat = max((compChambPress/sucChambPress),critPress);
	}
	else
	{
		sucPressRat = max((sucChambPress/compChambPress),critPress);
	}

}

void Orifice::calcDisPressRat(double compChambPress, double disChambPress)
{
	if(compChambPress <= disChambPress)
	{
		disPressRat = max((compChambPress/disChambPress),critPress);
	}
	else
	{
		disPressRat = max((disChambPress/compChambPress),critPress);
	}
}

void Orifice::calcTotSucMassFl(double sucMassFl)
{
	totSucMassFl += sucMassFl;
}

void Orifice::calcTotSucFl(double sucFlux)
{
	totSucFl += sucFlux;
}

void Orifice::calcTotSucBackf(double sucBackflow)
{
	totSucBackf +=  sucBackflow;
}

void Orifice::calcTotDisMassFl(double disMassFl)
{
	totDisMassFl += disMassFl;
}

void Orifice::calcTotDisFl(double disFlux)
{
	totDisFl += disFlux;
}

void Orifice::calcTotDisBackf(double disBackflow)
{
	totDisBackf += disBackflow;
}

void Orifice::setTotSucMassFl(double totSucMassFlVal)
{
	totSucMassFl = totSucMassFlVal;
}

void Orifice::setTotSucFl(double totSucFlVal)
{
	totSucFl = totSucFlVal;
}

void Orifice::setTotSucBackf(double totSucBackfVal)
{
	totSucBackf = totSucBackfVal;
}

void Orifice::setTotDisMassFl(double totDisMassFlVal)
{
	totDisMassFl = totDisMassFlVal;
}

void Orifice::setTotDisFl(double totDisFlVal)
{
	totDisFl = totDisFlVal;
}

void Orifice::setTotDisBackf(double totDisBackfVal)
{
	totDisBackf = totDisBackfVal;
}


double Orifice::getTotSucMassFl()
{
	return totSucMassFl;
}

double Orifice::getTotSucFl()
{
	return totSucFl;
}

double Orifice::getTotSucBackf()
{
	return totSucBackf;
}

double Orifice::getTotDisMassFl()
{
	return totDisMassFl;
}

double Orifice::getTotDisFl()
{
	return totDisFl;
}

double Orifice::getTotDisBackf()
{
	return totDisBackf;
}

string Orifice::getDirection()
{
	return direction;
}

double Orifice::getSpecHeatRatMed()
{
	return specHeatRatMed;
}

