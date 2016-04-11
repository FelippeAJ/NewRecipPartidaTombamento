#ifndef ROD_H
#define ROD_H

#include "Input.h"

class Rod
{
public:
	Rod();

	void setLength(double lengthValue);

	double getLength();

protected:
	double length;
};

#endif