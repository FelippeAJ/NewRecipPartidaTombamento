#include "GlobalHeatTransfer.h"

GlobalHeatTransfer::GlobalHeatTransfer()
{
	inputEnergyRateSum = 0;
	outputEnergyRateSum = 0;
}

void GlobalHeatTransfer::calcUA(double temperatureOne, double temperatureTwo)
{
	UA = (inputEnergyRateSum - outputEnergyRateSum)/(temperatureOne - temperatureTwo);
}

void GlobalHeatTransfer::calcInputEnergyRateSum(int n, ...)
{
	vector<double> inputEnergyRate;
	double val;
	va_list vl;
	va_start(vl,n);
	for (int i=0;i<n;i++)
	{
		val=va_arg(vl,double);
		inputEnergyRate.push_back(val);
	}

	va_end(vl); 

	for(std::vector<double>::iterator j = inputEnergyRate.begin();j!= inputEnergyRate.end();++j)
		inputEnergyRateSum += *j;
}

void GlobalHeatTransfer::calcOutputEnergyRateSum(int n, ...)
{
	vector<double> outputEnergyRate;
	double val;
	va_list vl;
	va_start(vl,n);
	for (int i=0;i<n;i++)
	{
		val=va_arg(vl,double);
		 outputEnergyRate.push_back(val);
	}

	va_end(vl); 

	for(std::vector<double>::iterator j =  outputEnergyRate.begin();j!=  outputEnergyRate.end();++j)
		outputEnergyRateSum += *j;
}

double GlobalHeatTransfer::getUA()
{
	return UA;
}

double GlobalHeatTransfer::getInputEnergyRateSum()
{
	return inputEnergyRateSum;
}

double GlobalHeatTransfer::getOutputEnergyRateSum()
{
	return outputEnergyRateSum;
}

void GlobalHeatTransfer::setInputEnergyRateSum(double inputEnergyRateSumValue)
{
	inputEnergyRateSum = inputEnergyRateSumValue;
}

void GlobalHeatTransfer::setOutputEnergyRateSum(double outputEnergyRateSumValue)
{
	outputEnergyRateSum = outputEnergyRateSumValue;
}