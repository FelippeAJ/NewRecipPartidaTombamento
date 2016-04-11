#include "NewtonRaphson.h"
#include "NumericalRecipes.h"

NewtonRaphson::NewtonRaphson()
{

}

void NewtonRaphson::calcDeltaT(vector<vector<double>> jacobianMatrix, vector<double> res)
{
	MatDoub a;
	MatDoub b;

	a.resize(jacobianMatrix.size(), jacobianMatrix[0].size());
	b.resize(jacobianMatrix.size(),1);

	for(int i = 0; i < jacobianMatrix.size(); i++)
	{
		for(int j = 0; j < jacobianMatrix[i].size(); j++)
		{
			a[i][j] = jacobianMatrix[i][j];
		}
		b[i][0] = res[i];
	}

	gaussj(a,b);

	deltaT.resize(b.nrows());

	for(int i = 0; i < jacobianMatrix.size(); i++)
	{
		deltaT[i] = b[i][0];
	}
}

vector<double> NewtonRaphson::getDeltaT()
{
	return deltaT;
}