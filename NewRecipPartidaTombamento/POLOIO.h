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
	double getParamVal(string name, string direction);
	string getWord(string name, string direction);
	double getParamVal(string name1, string name2, string direction);
	double getParamVal(string name1, string name2, string name3, string direction);
	string getWord(string name1, string name2, string name3, string direction);
	double getParamVal(string name1, string name2, string name3, string name4, string direction);
	void writeVariable(string name, double value, string direction);
	vector<vector<double>> getMatrix(string name, string direction, int numberOfLines);
	vector<double> getColumnMatrix(string name, string direction, int numberOfLines, double columnNumber);
	vector<vector<string>> getStringMatrix(string name, string direction, int numberOfLines);
	vector<double> getColumnMatrix(string name, string direction, int numberOfLines, int columnNumber);
	vector<double> getColumnMatrix(string name1, string name2, string direction, int numberOfLines, int columnNumber);


protected:
	void contNumberOfLines();
	void setStringMatrix();
	char fileName[200];
	int numberOfLines;
	double variableValue;
	string word;
	vector<vector<double>> doubleMatrix;
	vector<vector<string>> stringMatrix;


	int contador;
};

#endif;