#include "DynamicSystemFactory.h"
#include "DynamicSystem.h"

DynamicSystemFactory::DynamicSystemFactory()
{

}

void DynamicSystemFactory::creatDynamicSystem()
{
	Input readDynamicSystemNumber;

	readDynamicSystemNumber.contOrificesNumber();

	dynamicSystem = new DynamicSystem[readDynamicSystemNumber.getOrificesNumber()];

	DynamicSystem::id = 0;
}

