#ifndef STOPPER_H
#define STOPPER_H

#include "Input.h"

class Stopper
{
public:
	Stopper();

	void setHeight(double heightValue);

	double getHeight();

protected:
	double height;
};

#endif