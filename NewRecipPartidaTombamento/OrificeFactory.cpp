#include "OrificeFactory.h"
#include "Orifice.h"

OrificeFactory::OrificeFactory()
{
	

}

void OrificeFactory::creatOrifice()
{
	POLOIO POLOIOobj("input.dat");
	orifNum	=	POLOIOobj.getParamVal("orifices_number", "left");

	orifice = new Orifice[orifNum];

	Orifice::id = 0;
}

double OrificeFactory::getOrifNum()
{
	return orifNum;
}