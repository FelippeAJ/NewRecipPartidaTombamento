#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Interpolation
{
public:
	Interpolation();

	double polynomialInterp(double coefNumber, vector<double> coeficients, double desl);

protected:

};

#endif
