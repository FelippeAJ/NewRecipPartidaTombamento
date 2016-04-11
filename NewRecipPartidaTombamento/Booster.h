#ifndef BOOSTER_H
#define BOOSTER_H

#include <cmath>
#include "Constants.h"
#include "Input.h"

class Booster
{
public:
	Booster();

	void setHeight(double heightValue);

	double getHeight();

protected:
	double height;
};

#endif