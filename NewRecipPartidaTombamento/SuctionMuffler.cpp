#include "SuctionMuffler.h"

SuctionMuffler::SuctionMuffler()
{
	POLOIO POLOIOobj("SUCMUFFLER.dat");

	//expTemp			=	POLOIOobj.getParamVal("suc_muffler","pressure_convergence_criterion", "left");
	pressConvergCrit =	POLOIOobj.getParamVal("suc_muffler","pressure_convergence_criterion", "left");
	massConvergCrit =	POLOIOobj.getParamVal("suc_muffler","mass_convergence_criterion", "left");
	tempConvergCrit =	POLOIOobj.getParamVal("suc_muffler","temperature_convergence_criterion", "left");
	velRelaxCoef =		POLOIOobj.getParamVal("suc_muffler","velocity_relaxation_coefficient", "left");
	pressRelaxCoef =	POLOIOobj.getParamVal("suc_muffler","pressure_relaxation_coefficient", "left");
	tempRelaxCoef =		POLOIOobj.getParamVal("suc_muffler","temperature_relaxation_coefficient", "left");
	zeroFlFricFact =	POLOIOobj.getParamVal("suc_muffler","zero_flow_friction_factor", "left");
	chambNum =			POLOIOobj.getParamVal("suc_muffler","chamber_number", "left");
	entTemp =			POLOIOobj.getParamVal("suc_muffler","entrance_temperature", "left");
	
	volNum = 0;
	massResid = 0;
	pressResid = 0;
	cont = 0;
}


void SuctionMuffler::dimenVec()
{
	p.resize(volNum+2, 0);
	T.resize(volNum+2, 0);
	u.resize(volNum+2, 0);
    u0.resize(volNum+2, 0);
	T0.resize(volNum+2, 0);
	Taux.resize(volNum+2, 0);
    p0.resize(volNum+2, 0);
	ccp.resize(volNum+2, 0);
	ro.resize(volNum+2, 0);
	ro0.resize(volNum+2, 0);
	Fe.resize(volNum+2, 0); 
	Fw.resize(volNum+2, 0);
	f.resize(volNum+2, 0);
	apu.resize(volNum+2, 0); 
	aeu.resize(volNum+2, 0); 
	awu.resize(volNum+2, 0); 
	spu.resize(volNum+2, 0); 
	suu.resize(volNum+2, 0);
	Re.resize(volNum+2, 0);
	dx.resize(volNum+2, 0);
	DTp.resize(volNum+2, 0);
	Du.resize(volNum+2, 0);
	ATp.resize(volNum+2, 0);
	Au.resize(volNum+2, 0);
	chambId.resize(volNum+2, 0);	
	rou.resize(volNum+2, 0);
	rou0.resize(volNum+2, 0);
	d.resize(volNum+2, 0);


	app.resize(volNum+2, 0);
	aep.resize(volNum+2, 0); 
	awp.resize(volNum+2, 0); 
	sup.resize(volNum+2, 0);
	roe.resize(volNum+2, 0);
	row.resize(volNum+2, 0);
	mrop.resize(volNum+2, 0);
	mroe.resize(volNum+2, 0);
	mrow.resize(volNum+2, 0);
	mue.resize(volNum+2, 0);
	muw.resize(volNum+2, 0);

	apT.resize(volNum+2, 0);
	aeT.resize(volNum+2, 0);
	awT.resize(volNum+2, 0); 
	suT.resize(volNum+2, 0);
}

void SuctionMuffler::simul(double massFl, double sucChambPress, double sucChambTemp, double compChambTemp, double extTemp, double sucLinePress)						
{
	tempResid = 1;
	massResid = 1;
	pressResid = 1;

	int nk, ni;

	if(cont == 0)
	{
		readGeomDat();

		cont++;

		refrig.setTemp(sucChambTemp); 
		refrig.setPress(sucChambPress);

		refrig.calcRho();
		refrig.calcSpecHeat();
		refrig.calcViscThermConduc();

		cp	  = refrig.getCp();
		visc  = refrig.getVisc();
		kt	  = refrig.getThermConduc();
		R	  = refrig.getGasCt();

		boundCond(sucLinePress,extTemp,compChambTemp);
		inicVect(sucChambTemp - 273.15);
		boundCond(sucLinePress,extTemp,compChambTemp);
	}

	boundCond(sucLinePress,extTemp,compChambTemp);

	ni = 0;
	
	while(tempResid > tempConvergCrit)
	{
		nk = 0;
			
		 while(massResid > massConvergCrit || pressResid > pressConvergCrit)
		 {
			 calcVel(massFl);

			 calcPress(massFl);

			 nk++;

			 if(nk > 1500)
			 {
				massResid = 1E-10;
				pressResid  = 1E-10;
			 }
		 }

		massResid = 1.0;
		pressResid = 1.0;

		ni++;

		if(ni > 100)
		{	
			tempResid = 1E-10;	
		}

		calcTemp(massFl, compChambTemp);

	 }

	tempResid = 1.0;

	for(int i = 0; i < volNum+2; i++)
	{
		u0[i] = u[i];
		ro0[i] = ro[i];
		p0[i] = p[i];
		T0[i] = T[i];
	 }

	 sucChambPress = p[volNum];
}

void SuctionMuffler::readGeomDat()
{
	double dxmed;
	vector<double> Ltubo,Dtubo,Lcam,Dcam;
	int tubesNumber;

	string s;
	ostringstream temp;
	
	tubesNumber = chambNum -1;

	Ltubo.resize(tubesNumber ,0);
	Dtubo.resize(tubesNumber,0);
	tubeVolNum.resize(tubesNumber,0);
	Lcam.resize(chambNum,0);
	Dcam.resize(chambNum,0);

	
	POLOIO POLOIOobj("SUCMUFFLER.dat");

	int id;

	string idStr;

	for(id = 0; id < chambNum; id++)
	{
		idStr = to_string(id);

		Lcam[id] = POLOIOobj.getParamVal("suc_muffler","chamber_length",idStr, "left"); 
		Dcam[id] = POLOIOobj.getParamVal("suc_muffler","chamber_diameter",idStr, "left");
	}

	for(int i = 0; i < tubesNumber; i++)
	{
		idStr = to_string(i);

		Ltubo[i] = POLOIOobj.getParamVal("suc_muffler","tube_length",idStr, "left"); 
		Dtubo[i] = POLOIOobj.getParamVal("suc_muffler","tube_diameter",idStr, "left");
		tubeVolNum[i] = POLOIOobj.getParamVal("suc_muffler","tube_volumes_number",idStr, "left");

		volNum += tubeVolNum[i];
	}

	volNum += chambNum;

	dimenVec();		

	int k = 2;

	for(int i = 0; i < tubesNumber; i++)
	{
		for(int j = k; j <= k+tubeVolNum[i]-1; j++)
		{
			dx[j]  = Ltubo[i]/tubeVolNum[i];
		}

		k = k + tubeVolNum[i] + 1;
	}


	int j = 1;
	for(int i = 0; i < tubesNumber; i++) 
	{	
		dx[j] = Lcam[i];
		DTp[j] = Dcam[i];
		Du[j] = Dtubo[i];
		ATp[j] = (cte.Pi*pow(DTp[j], 2))/4;
		Au[j] = (cte.Pi*pow(Du[j],2))/4	;
		chambId[j] = 1;							
		
		j = j + tubeVolNum[i] + 1;
	}

	dx[volNum]	= Lcam[chambNum-1];
	DTp[volNum] = Dcam[chambNum-1];
	Du[volNum]	= DTp[volNum];
	ATp[volNum] = (cte.Pi*pow(DTp[volNum], 2))/4;
	Au[volNum]	= (cte.Pi*pow(Du[volNum],2))/4	;
	chambId[volNum]	= 1;	


	k = 2;

	for(int i = 0; i < tubesNumber; i++)
	{
		for(int j = k; j <= k+tubeVolNum[i]-1; j++)
		{
			DTp[j] = Dtubo[i];
			Du[j] = DTp[j];
			ATp[j] = (cte.Pi*pow(DTp[j], 2))/4;
			Au[j] = (cte.Pi*pow(Du[j],2))/4	;
		}

		k = k + tubeVolNum[i] + 1;
	}
}

void SuctionMuffler::boundCond(double sucLinePress, double extTempVal, double compChambTemp)
{
	p[1] = sucLinePress;					
	T[1] = entTemp + 273.15;		
	T[volNum+1] = compChambTemp;			
    extTemp = extTempVal;				
}

void SuctionMuffler::inicVect(double sucChambTemp)
{

	double R = refrig.getGasCt();

	double Tini;

	Tini = (0.7*entTemp + 0.3*sucChambTemp) + 273.15;

	for(int i =0; i < volNum +2; i++)
	{
		u[i] = 1.E-9;
		u0[i] = u[i];
		T[i] = Tini;
		T0[i] = T[i];
		Taux[i] = T[i];
		p[i] = p[1];
		p0[i] = p[i];
		ccp[i] = 0.0;
		ro[i] = p[i]/(R*T[i]);
		ro0[i] = ro[i];
	}
}

void SuctionMuffler::calcVel( double massFl)
{
	massResid  = 0;

	double leff,fm,Cc;
	double Di,So,Si;
	double ze, zw;
	int ini, fim;
	

	for(int i =0; i < volNum+1; i++)
	{
		if(u[i] > 0.0)
		{
			rou[i] = ro[i];
			rou0[i] = ro0[i];
		}
		else
		{
			rou[i] = ro[i+1];
			rou0[i] = ro0[i+1];
		}

	}

	for(int i = 1; i < volNum; i++)
	{
		Re[i] = abs(rou[i]*DTp[i]*u[i]/visc);
        
		if(Re[i] > 2300)
		{	
			if(Re[i] > 2300) 
			{
				f[i] = 0.3164/(pow(Re[i],0.25));
			}
		}
		else
		{
			f[i] = 64/(Re[i]) ;
		}

		if(massFl < 1.0e-7)
		{
			f[i] = f[i]*zeroFlFricFact;
		}

		spu[i] = -abs(rou[i]*f[i]*u[i]*Du[i]*dx[i]*cte.Pi/8)*u[i];
        suu[i] = spu[i] + (p[i] - p[i+1])*Au[i]+ (rou0[i]*dx[i]*Au[i]*u0[i]/dt);

	}

	for(int i = 1; i < volNum; i++) 
	{
		Fw[i] = ro[i]*(u[i-1] + u[i])/2.0;
		Fe[i] = ro[i+1]*(u[i] + u[i+1])/2;
		Di = visc/dx[i];
  
        aeu[i] = (Di + max(0.0,-Fe[i]))*ATp[i+1];
        awu[i] = (Di + max(Fw[i],0.0))*ATp[i];
        apu[i] = aeu[i] + awu[i] + ((rou[i]*dx[i]*Au[i])/dt);


		if(chambId[i] == 1 || chambId[i+1] == 1) 
		{
			 if(chambId[i] == 1)
			 {
				 leff = dx[i+1]/2;
				 fm = abs(ro[i+1]*Au[i]*u[i]);

				 if (u[i] >0.0) 
				 {
					 So = 1;
					 Si = ATp[i]/Au[i];
					 Cc = 0.62 + 0.38*pow((Au[i]/ATp[i]),3);
				 }
				 else 
				 {
					 So = ATp[i]/Au[i];
					 Si = 1;
					 Cc = 1;
				 }
			 }
			 else 
			 {
				 leff = dx[i]/2;
				 fm = abs(ro[i]*Au[i]*u[i]);

				 if (u[i] > 0.0)
				 {
					 So = ATp[i+1]/Au[i];
					 Si = 1;
					 Cc = 1;
				 }
				 else
				 {
					 So = 1;
					 Si = ATp[i+1]/Au[i];
					 Cc = 0.62 + 0.38*pow((Au[i]/ATp[i+1]),3);
				 }
			 }

			 apu[i] = fm/2*((pow((1./So),2) - pow((1./Si),2))+ pow((1./So - 1./Cc),2)) + leff*rou[i]*Au[i]/dt;
			 aeu[i] = 0;
			 awu[i] = 0;
			 suu[i] = Au[i]*(p[i] - p[i+1]) + leff*rou0[i]*u0[i]*Au[i]/dt;
		}


		d[i] = Au[i]/apu[i];  

		apu[i] = apu[i]/velRelaxCoef;
		suu[i] = suu[i] + (1 - velRelaxCoef)*apu[i]*u[i];
		d[i] = d[i]*velRelaxCoef;

	    massResid = massResid + abs(aeu[i]*u[i+1] + awu[i]*u[i-1] + suu[i]- apu[i]*u[i]); 
	}

	

		u = TDMA(1,volNum-1,aeu,awu,apu,suu,u);
}

void SuctionMuffler::calcPress(double massFl)
{
	int ini, fim;
	double ze, zw;
	pressResid  = 0;

	ini = 2;
	fim = volNum + 1;

	for(int i = 2; i < volNum + 1; i++)
	{
		 if(u[i] > 0.0)
		 {
			ze = 0.5;
		 }
         else
		 {
			ze = -0.5;
		 }
  
         if(u[i-1] > 0.0)
		 {
			zw = 0.5;
		 }
         else
		 {
			zw = -0.5;
		 }

		 roe[i] = (0.5 + ze)*ro[i] + (0.5 - ze)*ro[i+1];
		 row[i] = (0.5 + zw)*ro[i-1] + (0.5 - zw)*ro[i];

		 mroe[i] = (0.5 - ze)*u[i]*Au[i];
		 mrow[i] = -(0.5 + zw)*u[i-1]*Au[i-1];
		 mrop[i] = (0.5 + ze)*u[i]*Au[i] - (0.5 - zw)*u[i-1]*Au[i-1]+ ATp[i]*dx[i]/dt;

		 mue[i] = roe[i]*Au[i];
		 muw[i] = row[i]*Au[i-1];

		 aep[i] = mue[i]*d[i] - (0.5 - ze)*Au[i]*u[i]/(R*T[i+1]);
		 awp[i] = muw[i]*d[i-1] + (0.5 + zw)*u[i-1]*Au[i-1]/(R*T[i-1]);
		 app[i] = mue[i]*d[i] + (0.5 + ze)*Au[i]*u[i]/(R*T[i+1])+ muw[i]*d[i-1] + (0.5 - zw)*u[i-1]*Au[i-1]/(R*T[i-1])+ ATp[i]*dx[i]/(R*T[i]*dt);

		 sup[i] = -roe[i]*Au[i]*u[i] + row[i]*Au[i-1]*u[i-1]- (ro[i] - ro0[i])*ATp[i]*dx[i]/dt;

		 double a, b, c;

		 a = -roe[i]*Au[i]*u[i];

		 b = + row[i]*Au[i-1]*u[i-1];

		 c = - (ro[i] - ro0[i])*ATp[i]*dx[i]/dt;

		 if(i == volNum)
		 {
			 aep[i] = 0.0;
			 awp[i] = muw[i]*d[i-1]+ (0.5+zw)*u[i-1]*Au[i-1]/(R*T[i-1]);
			 app[i] = +(0.5-zw)*u[i-1]*Au[i-1]/(R*T[i-1])+ muw[i]*d[i-1] + ATp[i]*dx[i]/(R*T[i]*dt);
			 sup[i] = -massFl + row[i]*Au[i-1]*u[i-1]- (ro[i] - ro0[i])*ATp[i]*dx[i]/dt;
		 }

		 pressResid = pressResid + abs(sup[i]);
	}

	ccp = TDMA(ini,fim -1,aep,awp,app,sup,ccp);

	for(int i = 1 ; i < volNum; i++)
	{
		u[i] = u[i] + d[i]*(ccp[i] - ccp[i+1]);
	}

	for(int i = volNum; i >=2 ; i--)
	{
		 p[i] = p[i] + pressRelaxCoef*ccp[i];
         ccp[i] = 0;
	}

	for(int i = 2; i < volNum+1; i++)
	{
		 ro[i] = p[i]/(R*T[i]);
	}

	ro[volNum+1] = ro[volNum];
}

void SuctionMuffler::calcTemp(double massFl, double compChambTemp)
{
	double me, mw;
	double ReT;
	double UA;
	
	double z, he, ks;
	double M0, M, V, Pr, Nu, hi;

	int ini, fim;
	double ze, zw;
	tempResid = 0;

	he = 8.0;

	ini = 2;
	fim = volNum + 1;

	for(int i = 1; i < volNum +1; i++)
	{
		if(u[i] > 0.0)
		{
              roe[i] = ro[i];
              row[i] = ro[i-1];
		}
		else
		{
              roe[i] = ro[i+1];
              row[i] = ro[i];
		}
	}

	for(int i = 2; i < volNum+1; i++)	
	{
		 if(u[i] > 0.0)

		 {
			ze = 0.5;
		 }
         else
		 {
			ze = -0.5;
		 }
  
         if(u[i-1] > 0.0)
		 {
			zw = 0.5;
		 }
         else
		 {
			zw = -0.5;
		 }

		 ks = 0.18;

		 Pr = visc*cp/kt;
		 ReT = abs(roe[i]*u[i]*DTp[i]/visc);

		 if(ReT > 2300)
		 {
			Nu = 0.023*pow(ReT,(0.8))*pow(Pr,(1./3));
		 }
		 else
		 {
				Nu = 3.66;
		 }

		 hi = Nu*kt/DTp[i];
		 UA = (DTp[i]*cte.Pi*dx[i])/(DTp[i]/((DTp[i]+4.0E-3)*he) + DTp[i]/(2*ks)*log((DTp[i]+4.0E-3)/DTp[i]) + 1/hi);

		 V = dx[i]*ATp[i];
		 M = ro[i]*V;
		 M0 = ro0[i]*V;

		 me = roe[i]*u[i]*Au[i];
		 mw = row[i]*u[i-1]*Au[i-1];

		 aeT[i] = -me*cp*(0.5 - ze) + 2*kt*Au[i]/(dx[i+1]+dx[i]);
		 awT[i] = +mw*cp*(0.5 + zw) + 2*kt*Au[i-1]/(dx[i-1]+dx[i]);
		 apT[i] = aeT[i] + awT[i] + cp*M0/dt + UA;
		 suT[i] = V/dt*(p[i]-p0[i]) - M/dt*(pow( ( ( u[i]+u[i-1] ) /2 ) ,2) )/2 + M0/dt*(cp*T0[i] + pow((((u0[i]+u0[i-1])/2)), 2)/2)+ mw*pow(u[i-1],2)/2. - me*pow(u[i],2)/2 + UA*extTemp;																
										
		if(i == volNum)
		{
			apT[i] = awT[i] - (0.5-ze)*massFl*cp + cp*M0/dt + UA;
			aeT[i] = 0.0;
			suT[i] = V/dt*(p[i]-p0[i]) + M0*cp*T0[i]/dt + UA*extTemp - (0.5-ze)*massFl*cp*compChambTemp;										
		}

		apT[i] = apT[i]/tempRelaxCoef;
		suT[i] = suT[i] + (1.-tempRelaxCoef)*apT[i]*T[i];

	}

	T = TDMA(ini,fim -1,aeT,awT,apT,suT,T);

	for(int i = 2; i < volNum +1; i++)
	{
		tempResid = tempResid + abs(T[i] - Taux[i]);
		Taux[i] = T[i];
	    ro[i] = p[i]/(R*T[i]);
	}

	 ro[volNum+1] = ro[volNum];
}

vector<double> SuctionMuffler::TDMA(int ISTART,int IEND, vector<double> ae, vector<double> aw, vector<double> ap, vector<double> su, vector<double> PHI)
{
	vector<double> A, B, C, D;
	double TERM;
	int NIM1, ISTM1;

	A.resize(IEND + 1,0);
	B.resize(IEND + 1,0);
	C.resize(IEND + 1,0);
	D.resize(IEND + 1,0);

    NIM1 = IEND;
    ISTM1 = ISTART-1;
    
	A[ISTM1] = 0;
    C[ISTM1] = PHI[ISTM1];

	for(int I = ISTART; I <= NIM1; I++)
	{
		B[I]=aw[I];
		D[I]=ap[I];

		TERM = 1/(D[I]-B[I]*A[I-1]);
			
		A[I]=ae[I]*TERM;
		C[I]=(su[I]+B[I]*C[I-1])*TERM;
	}

	for(int II = NIM1; II >= ISTART; II--)
	{
		PHI[II]=A[II]*PHI[II+1]+C[II];
	}

	return PHI;
}

void SuctionMuffler::calcDt(double deltaTheta, double shaftVel)
{
	dt = deltaTheta/shaftVel;
}

