#include "CompressionChamber.h"

double CompressionChamber::Rey = 0;

double CompressionChamber::Pran = 0;

double CompressionChamber::Nus = 0;

double CompressionChamber::heatTransfArea = 0;

double CompressionChamber::convCoef = 0;

string CompressionChamber::shape = "straight";

double CompressionChamber::derivVol = 0;

double CompressionChamber::area = 0;

double CompressionChamber::pistDiam = 0;

double CompressionChamber::distBottPistPin = 0;

CompressionChamber::CompressionChamber()
{
	POLOIO POLOIOObj("input.dat");

	shape			= POLOIOObj.getWord("cylinder", "left");
	bore			= POLOIOObj.getParamVal("bore", "left");
	deadVol			= POLOIOObj.getParamVal("dead_volume", "left");
	length			= POLOIOObj.getParamVal("length", "left");
	conLength		= POLOIOObj.getParamVal("conic_length", "left");
	shaftDist		= POLOIOObj.getParamVal("shaft_distance", "left");
	pistHeadLength  = POLOIOObj.getParamVal("piston_head_length", "left");
	pistSkirtLength = POLOIOObj.getParamVal("piston_skirt_length", "left");
	gap				= POLOIOObj.getParamVal("gap", "left");
	gapInfDeadPt	= POLOIOObj.getParamVal("gap_inferior_dead_point", "left");		
	expTemp			= POLOIOObj.getParamVal("cylinder_wall", "left") + 273.15;
}

void CompressionChamber::calcInicProp(Mechanism mech, double sucChambPress, double sucChambRho, double sucChambExpTemp)
{
	calcArea();

	if(mech.getMech() == "crank_rod")
	{
		calcDispVol(2*mech.getEccent());
	}
	else
	if(mech.getMech() == "sinusoidal")
	{
		calcDispVol(mech.getStroke());
	}

	calcVol(mech.getSupDeadPt(), mech.getPos()); 
	refrig.setTemp(sucChambExpTemp);
	refrig.setPress(sucChambPress);
	
	refrig.calcRho();
	
	refrig.setRho(sucChambRho);
	refrig.calcMass(vol);

	calcPistDiam();

	calcContactLength();
}

void CompressionChamber::calcTemp(Mechanism mechObj, double sucChambH, double disChambH, SuctionSystem sucSystObj, DischargeSystem disSystObj, double timeStep, double leakMassFl)
{
	double TCIL, PCIL;

	calcVol(mechObj.getSupDeadPt(),  mechObj.getPos());
	refrig.calcRho(vol);
	refrig.calcViscThermConduc();
	refrig.calcSpecHeat();
	refrig.calcH();
	refrig.calcDpresDtemp();

	calcRey(refrig.getRho(),  mechObj.getVelMed(), bore, refrig.getVisc());
	calcPran(refrig.getVisc(), refrig.getCp(), refrig.getThermConduc());
	calcNus();

	calcHeatTransfArea(mechObj.getSupDeadPt(),  mechObj.getPos());
	calcConvCoef();

	calcDerivVol( mechObj.getVel());
	calcDerivTemp(sucChambH, disChambH,  sucSystObj.orifFact.orifice[0].getTotSucFl(),  sucSystObj.orifFact.orifice[0].getTotSucBackf(),  disSystObj.orifFact.orifice[1].getTotDisFl(),  disSystObj.orifFact.orifice[1].getTotDisBackf(), leakMassFl);
	refrig.calcTempExplic(derivTemp, timeStep);
}

//Mechanism

void CompressionChamber::calcGapFricFact(double sucLinePress, double mechanVel)
{
	double diameterRatio = pistDiam/bore;

	double A = log(diameterRatio);

	double B = pow(diameterRatio, 2);

	oilObj.calcViscosity(expTemp);

	gapFricFact= -( ( ( 2*cte.Pi*oilObj.getViscosity()*contLength) / A)*mechanVel	+  ((refrig.getPress() - sucLinePress)/2.0)*cte.Pi*pow((pistDiam/2),2)*((2.0 * B * A + 1.0 - B)/A ) );
}

void CompressionChamber::calcContactLength()
{
	contLength = pistHeadLength + pistSkirtLength;
}

double CompressionChamber::getGapFricFact()
{
	return gapFricFact;
}

//AdmNumber

void CompressionChamber::calcRey(double rho, double vel, double caractLength, double visc)
{
	Rey = (rho*vel*caractLength)/visc;
}

void CompressionChamber::calcPran(double visc,double cp, double thermConduct)
{
	Pran = (visc*cp)/thermConduct;
}

void CompressionChamber::calcNus()
{
	Nus = 0.7*pow(Rey*Pran,0.7);
}

//HeatTransfer

void CompressionChamber::calcHeatTransfArea(double supDeadPt, double mechPos)
{
	Constants cte;

	heatTransfArea = 2*area + 4*deadVol/bore + cte.Pi*bore*(supDeadPt - mechPos);
}

void CompressionChamber::calcConvCoef()
{
	convCoef = (Nus*refrig.getThermConduc())/bore;
}

// Cylinder

void CompressionChamber::calcArea()
{
	Constants cte;

	area = (cte.Pi*pow(bore,2))/4 ;
}

void CompressionChamber::calcVol(double supDeadPt, double mechPos)
{
	vol = deadVol + area*( supDeadPt - mechPos);
}

void CompressionChamber::calcDispVol(double stroke)
{
	dispVol = stroke*area;
}

void CompressionChamber::calcDerivVol(double mechVel)
{
	derivVol = -area*mechVel;
}

void CompressionChamber::calcDerivTemp(double sucChambH, double disChambH, double sucFl, double sucfBackf, double disFl, double disBackf, double leakMassFl)
{
	double A = 1/(refrig.getMass()*refrig.getCv());

	double B = convCoef*heatTransfArea;

	double C = A*(B*(expTemp) + sucFl*(sucChambH - refrig.getH()) + disBackf*(disChambH - refrig.getH()));

	double D = A*(B +  refrig.getDPresDTemp()*derivVol - refrig.getDPresDTemp()*(1/refrig.getRho())*(sucFl - disFl - leakMassFl - sucfBackf + disBackf));
	
	derivTemp = C - D*refrig.getTemp();
}

void CompressionChamber::calcMassBal(double sucFl, double disFl, double leakFl, double timeStep)
{
	double massTemp = 0;

	massTemp = refrig.getMass() + (sucFl - disFl - leakFl)*timeStep;

	refrig.setMass(massTemp);
}

double CompressionChamber::getBore()
{
	return bore;
}

double CompressionChamber::getLength()
{
	return length;
}

double CompressionChamber::getConLength()
{
	return conLength;
}

double CompressionChamber::getShaftDist()
{
	return shaftDist;
}

double CompressionChamber::getArea()
{
	return area;
}

double CompressionChamber::getVol()
{
	return vol;
}

double CompressionChamber::getDeadVol()
{
	return deadVol;
}

double CompressionChamber::getDispVol()
{
	return dispVol;
}

double CompressionChamber::getDerivTemp()
{
	return derivTemp;
}

string CompressionChamber::getShape()
{
	return shape;
}

//Piston

void CompressionChamber::calcPistDiam()
{
	pistDiam = bore - gap;
}

void CompressionChamber::calcDistBottPistTop(double mechPos)
{
	distBottPistTop = mechPos + pistHeadLength - shaftDist;

	if(distBottPistTop > (pistHeadLength + pistSkirtLength))
	{
		distBottPistTop = pistHeadLength + pistSkirtLength;
	}
}

void CompressionChamber::calcDistBottPistPin()
{
	distBottPistPin = distBottPistTop - pistHeadLength;
}

double CompressionChamber::getPistHeadLength()
{
	return pistHeadLength;
}

double CompressionChamber::getPistSkirtLength()
{
	return pistSkirtLength;
}

double CompressionChamber::getDistBottPistPin()
{
	return distBottPistPin;
}

double CompressionChamber::getPistDiam()
{
	return pistDiam;
}


//Leak

void CompressionChamber::calcGapPistTop(double supDeadPt, double mechPos)
{
	if((supDeadPt - mechPos) > (length - conLength))
	{
		gapPistTop = gap + ((supDeadPt - mechPos) - (length - conLength))*(gapInfDeadPt - gap)/conLength;
	}
	else
	{
		gapPistTop = gap;
	}
}

void CompressionChamber::calcGapPistPin(double supDeadPt, double mechPos)
{
	if((supDeadPt - mechPos + pistHeadLength) > (length - conLength))
	{
		gapPistPin = gap + ((supDeadPt - mechPos + pistHeadLength) - (length - conLength))*(gapInfDeadPt - gap)/conLength;
	}
	else
	{
		gapPistPin = gap;
	}
}

void CompressionChamber::calcGapPistBott(double supDeadPt, double mechPos)
{
	if((supDeadPt - mechPos + pistHeadLength + distBottPistPin) > (length - conLength))
	{
		gapPistBott = gap + ((supDeadPt - mechPos + pistHeadLength + distBottPistPin) - (length - conLength))*(gapInfDeadPt - gap)/conLength;
	}
	else
	{
		gapPistBott = gap;
	}
}

void CompressionChamber::calcTopDiam()
{
	topDiam = bore - (gapPistTop + gapPistPin)/2;
}

void CompressionChamber::calcBottDiam()
{
	bottDiam = bore - (gapPistPin + gapPistPin)/2;
}


void CompressionChamber::calcLeakArea()
{
	if(shape == "straight")
	{
		leakArea = area - (cte.Pi*pow(pistDiam,2))/4;
	}
	else
	if(shape == "conic")
	{
		topArea  = area - (cte.Pi*pow(topDiam,2))/4;

		bottArea = area - (cte.Pi*pow(bottDiam,2))/4;
	}
}

double CompressionChamber::getGap()
{
	return gap;
}

double CompressionChamber::getGapPistTop()
{
	return gapPistTop;
}

double CompressionChamber::getGapPistPin()
{
	return gapPistPin;
}

double CompressionChamber::getGapPistBott()
{
	return gapPistBott;
}

double CompressionChamber::getTopDiam()
{
	return topDiam; 
}

double CompressionChamber::getBottDiam()
{
	return bottDiam; 
}

double CompressionChamber::getLeakArea()
{
	return leakArea;
}

double CompressionChamber::getTopArea()
{
	return topArea;
}

double CompressionChamber::getBottArea()
{
	return bottArea;
}