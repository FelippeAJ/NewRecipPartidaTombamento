#ifndef DYNAMICSYSTEM_H
#define DYNAMICSYSTEM_H

#include <cmath>
#include <vector>
#include "Constants.h"
#include "Input.h"
#include "Impeller.h"
#include "Valve.h"
#include "Booster.h"
#include "Stopper.h"
#include "EffectiveForceArea.h"


#include "SimulationParameters.h"


class DynamicSystem
{
public:
	DynamicSystem();

	void calcEquivalentMass();

	void calcStickingForceAct(int stickingForceIndice, string direction);
	void calcPreTensionForceAct();
	void calcResultantForce(double cylPress, double sucChamberPress, double disChamberPress, string orificeDirecion);

	void calcAccelaration();
	void calcDisplacement();
	void calcVelocity();
	
	void setNatFrequency(double natFrequencyValue);
	void setStiffness(double stiffnessValue);
	
	void setStickingForce(double stickingForceValue);

	double getResultantForce();

	double getAccelaration();
	double getVelocity();
	double getDisplacement();
	
	void incrementId();
	
	Impeller impeller;
	Valve valve;
	Booster booster;
	Stopper stopper;
	SimulationParameters simulParameters;
	EffectiveForceArea effectForceAreaObj;

	static int id;

//protected:
	double natFrequency;
	double stiffness;
	double equivalentMass;

	double stickingForce;
	double stickingForceAct;
	double preTensionAct;
	double resultantForce;

	double displacement;
	double velocity;
	double accelaration;

	double effectiveForceArea;

	
};

#endif