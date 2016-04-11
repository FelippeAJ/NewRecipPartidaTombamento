#ifndef POLOIO_H
#define POLOIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include  <iomanip>

using namespace std;

class POLOIO
{
public:
	POLOIO(char userFileName[200]);
	~POLOIO();
	double getVariable(string name, string direction);
	double getVariable(string name1, string name2, string direction);
	double getVariable(string name1, string name2, string name3, string direction);
	double getVariable(string name1, string name2, string name3, string name4, string direction);
	void writeVariable(string name, double value, string direction);
	vector<vector<double>> getMatrix(string name, string direction, int numberOfLines);
	vector<vector<string>> getStringMatrix(string name, string direction, int numberOfLines);

//protected:
	void contNumberOfLines();
	void setStringMatrix();
	char fileName[200];
	int numberOfLines;
	double variableValue;
	vector<vector<double>> doubleMatrix;
	vector<vector<string>> stringMatrix;


	int contador;
};

#endif;