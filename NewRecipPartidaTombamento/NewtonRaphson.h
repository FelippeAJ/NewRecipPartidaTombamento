#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

#include <iostream>
#include <vector>
#include "nr3.h"
#include "gaussj.h"

using namespace std;

class NewtonRaphson
{

public:
	NewtonRaphson();

	void calcDeltaT(vector<vector<double>> jacobianMatrix, vector<double> res);

	vector<double> getDeltaT();
	

protected:

	vector<double> deltaT;
};

#endif