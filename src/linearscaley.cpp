#include "linearscaley.h"

#include <math.h>


double LinearScaleY::plot2real(double val)const
{
	return (val-x0)/Mx;
};

int LinearScaleY::real2plot(double val)const
{
	return static_cast<int>(val*Mx+x0);
};

void LinearScaleY::changeDiapason (double dataDiapason, double plotDiapason)
{ 
	Mx = -plotDiapason/(testFlags(Scale::ManualDiapason) ? fabs(max-min) : dataDiapason);
	x0 = (int)( plotDiapason - min*Mx );
};

void  LinearScaleY::setRefPoint( double val, double pos, double d )
{
	max = val+d*(1-pos); 
    min = max-d;
};
