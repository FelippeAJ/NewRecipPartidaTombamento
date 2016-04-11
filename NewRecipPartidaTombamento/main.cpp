#include <iostream>
#include <fstream>
#include "Refrigerant.h"
#include "Compressor.h"
#include "POLOIO.h"


using namespace std;


int main()
{

	//POLOIO POLOIOobj("input.dat");

	//double test;

	//string s  = "0";

	//test = POLOIOobj.getParamVal("suclength",s, "right"); 

	//int id = 0;
	//vector<double> var;
	//var.resize(3,0);
	//double var2;

	//POLOIO POLOIOobj1("input.dat");
	//string idStr;

	///*for(double id = 0; id < 3; id++)
	//{*/

	//idStr = to_string(id);
	//var[0] =  POLOIOobj1.getParamVal("suc_chamber_diameter", idStr, "right");

	////}


	loadRefprop();

	setRefrigerant();

	Compressor compObj;

	compObj.silmulComp();






	system("PAUSE");
	return 0;
}