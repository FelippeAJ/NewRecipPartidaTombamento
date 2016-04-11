#ifndef DYNAMICSYSTEMFACTORY_H
#define DYNAMICSYSTEMFACTORY_H

#include "Input.h"
#include "DynamicSystem.h"

class DynamicSystemFactory
{
public:
	DynamicSystemFactory();

	void creatDynamicSystem();

	DynamicSystem *dynamicSystem;

protected:
};

#endif