#ifndef IMPELLER_H
#define IMPELLER_H

#include "Input.h"

class Impeller
{
public:
	Impeller();

	void setHeight(double heightValue);
	void setPreTension(double preTensionValue);

	double getHeight();
	double getPreTension(); 

protected:
	double height;
	double preTension;
};

#endif