#ifndef JACOBIAN_H
#define JACOBIAN_H

#include <iostream>
#include <vector>

using namespace std;

class Jacobian
{
public:
	Jacobian();

	void calcJacobianMatrix(vector<vector<double>> matrixA, vector<double> vectorA, vector<double> vectorB, double delta);

	vector<vector<double>> getJacobianMatrix();

	vector<double> vectorTemp;


protected:
	
	vector<vector<double>> jacobianMatrix;


};

#endif