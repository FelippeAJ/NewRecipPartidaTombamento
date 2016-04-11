#include "Interpolation.h"

Interpolation::Interpolation()
{

}

double Interpolation::polynomialInterp(double coefNumber, vector<double> coeficients, double desl)
{
	 int IA;
     double A=0.0,rend;

      if (desl==0.0)
         rend = coeficients[0];
      else
      {
         for (IA=0;IA<coefNumber;IA++)
            A = A + coeficients[IA]*pow(desl,(IA));
         rend = A;
      }
      return (rend);
}
