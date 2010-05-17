#include "linearscalex.h"
#include <math.h>

double LinearScaleX::plot2real(double val)const
{
	return (val-x0)/Mx;
};

int LinearScaleX::real2plot(double val)const
{
	return static_cast<int>(val*Mx+x0);
};

void LinearScaleX::changeDiapason (double dataDiapason, double plotDiapason)
{
	Mx = plotDiapason/(testFlags(Scale::ManualDiapason) ? fabs(max-min) : dataDiapason);
   //Calculate x0 in the intention what data value 0 is corresponded to 0 plot plot position.
	x0 = static_cast<int>(-min*Mx );
};

void LinearScaleX::setRefPoint( double val, double pos, double d )
{
	x0 = static_cast<int>( val - pos*Mx );
};
