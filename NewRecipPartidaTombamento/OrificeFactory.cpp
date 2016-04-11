#include "OrificeFactory.h"
#include "Orifice.h"

OrificeFactory::OrificeFactory()
{
	

}

void OrificeFactory::creatOrifice()
{
	readOrificeNumber.contOrificesNumber();

	orifice = new Orifice[readOrificeNumber.getOrificesNumber()];

	Orifice::id = 0;
}
