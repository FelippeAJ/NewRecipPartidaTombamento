#include "Jacobian.h"

Jacobian::Jacobian()
{

}

void Jacobian::calcJacobianMatrix(vector<vector<double> > matrixA, vector<double> vectorA, vector<double> vectorB, double delta)
{
	vectorTemp.resize( matrixA[0].size(), 0);

	jacobianMatrix.resize(matrixA.size(), vectorTemp);

	for(int i = 0; i < jacobianMatrix.size(); i++)
	{
		for(int j = 0; j < matrixA[0].size(); j++)
		{
			jacobianMatrix[i][j] = (matrixA[i][j] - vectorA[i])/(vectorB[j]*delta);
		}
	}


}

vector<vector<double>> Jacobian::getJacobianMatrix()
{
	return jacobianMatrix;
}