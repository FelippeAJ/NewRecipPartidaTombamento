#include "POLOIO.h"

POLOIO::POLOIO(char userFileName[200])
{
	strcpy(fileName,userFileName);

	numberOfLines = 0;

	contador = 0;

	contNumberOfLines();
	setStringMatrix();
}

POLOIO::~POLOIO()
{
}

void POLOIO::contNumberOfLines()
{
	ifstream infile;
	
	infile.open(fileName, ios::in);

	string line;
	while (getline(infile, line))
	{
		++contador;

	}

	infile.close();
}

void POLOIO::setStringMatrix()
{
	
	stringMatrix.resize(contador);

	ifstream infile;
	
	infile.open(fileName, ios::in);

	int line_number = 0;

	string line;
	while (getline(infile, line))
	{
	  istringstream buffer(line);
	  string word;

		while (buffer >> word)
		{
			stringMatrix[line_number].push_back(word);
		}

		 ++line_number;
	}

	infile.close();
}


double POLOIO::getVariable(string name,string direction)
{
	for(int i = 0; i < stringMatrix.size(); i++)
	{
		for(int j =0; j < stringMatrix[i].size(); j++)
		{
			
			if(stringMatrix[i][j] == name  && direction == "right")
			{
				if((j+1) < stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i][j+1].c_str());
				}
				else
				if((j+1) == stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i+1][0].c_str());
				}
			}
			else
			if(stringMatrix[i][j] == name && direction == "left")
			{
				if( j > 0)
				{
					variableValue = atof(stringMatrix[i][j-1].c_str());
				}
				else
				if( j == 0)
				{
					variableValue = atof(stringMatrix[i-1][stringMatrix[i-1].size()-1].c_str());
				}
				else
				if(j == 0 && i == 0)
				{
					cout << "Nao e possivel realizar essa leitura" << endl;
				}
			}
		}
	}

	return variableValue;
}

double POLOIO::getVariable(string name1, string name2, string direction)
{
	for(int i = 0; i < stringMatrix.size(); i++)
	{
		for(int j =0; j < stringMatrix[i].size(); j++)
		{
			
			if(stringMatrix[i][j] == name2 && stringMatrix[i][j-1] == name1 && direction == "right")
			{
				if((j+1) < stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i][j+1].c_str());
				}
				else
				if((j+1) == stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i+1][0].c_str());
				}
			}
			else
			if(stringMatrix[i][j] == name1 && stringMatrix[i][j+1] == name2  && direction == "left")
			{
				if( j > 0)
				{
					variableValue = atof(stringMatrix[i][j-1].c_str());
				}
				else
				if( j == 0)
				{
					variableValue = atof(stringMatrix[i-1][stringMatrix[i-1].size()-1].c_str());
				}
				else
				if(j == 0 && i == 0)
				{
					cout << "Nao e possivel realizar essa leitura" << endl;
				}
			}
		}
	}
	
	return variableValue;

}

double POLOIO::getVariable(string name1, string name2, string name3, string direction)
{
	for(int i = 0; i < stringMatrix.size(); i++)
	{
		for(int j =0; j < stringMatrix[i].size(); j++)
		{
			
			if(stringMatrix[i][j] == name3 && stringMatrix[i][j-1] == name2 && stringMatrix[i][j-2] == name1 && direction == "right")
			{
				if((j+1) < stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i][j+1].c_str());
				}
				else
				if((j+1) == stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i+1][0].c_str());
				}
			}
		}
	}
	
	return variableValue;
}

double POLOIO::getVariable(string name1, string name2, string name3, string name4, string direction)
{
	for(int i = 0; i < stringMatrix.size(); i++)
	{
		for(int j =0; j < stringMatrix[i].size(); j++)
		{
			
			if(stringMatrix[i][j] == name4 && stringMatrix[i][j-1] == name3 && stringMatrix[i][j-2] == name2 && stringMatrix[i][j-3] == name1  && direction == "right")
			{
				if((j+1) < stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i][j+1].c_str());
				}
				else
				if((j+1) == stringMatrix[i].size())
				{
					variableValue = atof(stringMatrix[i+1][0].c_str());
				}
			}
		}
	}
	
	return variableValue;

}

void POLOIO::writeVariable(string name, double value, string direction)
{

	ostringstream strs;
	strs << value;
	std::string valueString = strs.str();

	

	for(int i = 0; i < stringMatrix.size(); i++)
	{
		for(int j =0; j < stringMatrix[i].size(); j++)
		{
			if(stringMatrix[i][j] == name  && direction == "right")
			{
				if((j+1) < stringMatrix[i].size())
				{
					stringMatrix[i][j+1] = valueString;
				}
				else
				if((j+1) == stringMatrix[i].size())
				{
					stringMatrix[i+1][0] = valueString;
				}
			}
			else
			if(stringMatrix[i][j] == name && direction == "left")
			{
				if( j > 0)
				{
					stringMatrix[i][j-1] = valueString;
				}
				else
				if( j == 0)
				{
					stringMatrix[i-1][stringMatrix[i-1].size()-1] = valueString;
				}
				else
				if(j == 0 && i == 0)
				{
					cout << "Nao e possivel realizar essa leitura" << endl;
				}
			}
		}
	}

	
	
	ofstream writeValues;
	
	writeValues.open(fileName, ios::out);


	for(int i = 0; i < stringMatrix.size(); i++)
	{
		for(int j =0; j < stringMatrix[i].size(); j++)
		{
			writeValues << setprecision(5) << stringMatrix[i][j] << "\t";
		}

		writeValues << endl;


	}

	writeValues.close();

	


}

vector<vector<double>> POLOIO::getMatrix(string name, string direction, int numberOfLines)
{
	vector<vector<double>> doubleMatrix;
	doubleMatrix.resize(numberOfLines);

	vector<vector<string>> matrixTemp;
	matrixTemp.resize(numberOfLines);

	if(direction == "right")
	{
		for(int i = 0; i < stringMatrix.size(); i++)
		{
			for(int j =0; j < stringMatrix[i].size(); j++)
			{
				if(stringMatrix[i][j] == name)
				{
					for(int z = 1; z <= numberOfLines; z++)
					{
						for(int t = 0; t < stringMatrix[i+z].size(); t++)
						{
							matrixTemp[z-1].push_back(stringMatrix[i+z][t]);
							doubleMatrix[z-1].push_back(atof(stringMatrix[i+z][t].c_str()));
						}
					}
				}
			}
		}
	}
	else
	if(direction == "left")
	{
		int contador = -1;

		for(int i = 0; i < stringMatrix.size(); i++)
		{
			for(int j =0; j < stringMatrix[i].size(); j++)
			{
				if(stringMatrix[i][j] == name)
				{
					for(int z =  numberOfLines; z > 0; z--)
					{
						for(int t = 0; t < stringMatrix[i + contador].size(); t++)
						{
							matrixTemp[z-1].push_back(stringMatrix[i + contador][t]);
							doubleMatrix[z-1].push_back(atof(stringMatrix[i + contador][t].c_str()));
						}

						contador--;
					}
				}
			}
		}

	}

	return doubleMatrix;
}

vector<vector<string>> POLOIO::getStringMatrix(string name, std::string direction, int numberOfLines)
{
	vector<vector<string>> matrixTemp;
	matrixTemp.resize(numberOfLines);

	if(direction == "right")
	{
		for(int i = 0; i < stringMatrix.size(); i++)
		{
			for(int j =0; j < stringMatrix[i].size(); j++)
			{
				if(stringMatrix[i][j] == name)
				{
					for(int z = 1; z <= numberOfLines; z++)
					{
						for(int t = 0; t < stringMatrix[i+z].size(); t++)
						{
							matrixTemp[z-1].push_back(stringMatrix[i+z][t]);
						}
					}
				}
			}
		}
	}
	else
	if(direction == "left")
	{
		int contador = -1;

		for(int i = 0; i < stringMatrix.size(); i++)
		{
			for(int j =0; j < stringMatrix[i].size(); j++)
			{
				if(stringMatrix[i][j] == name)
				{
					for(int z =  numberOfLines; z > 0; z--)
					{
						for(int t = 0; t < stringMatrix[i + contador].size(); t++)
						{
							matrixTemp[z-1].push_back(stringMatrix[i + contador][t]);
						}

						contador--;
					}
				}
			}
		}

	}

	return matrixTemp;
}