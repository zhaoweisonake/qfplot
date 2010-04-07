#include "linearscaley.h"

#include <math.h>
/**
 * Constructors/Destructors
 */
/**
 * Methods
 */
void LinearScaleY::changeDiapason (double dataDiapason, double plotDiapason)
{ 
	Mx = -plotDiapason/(testFlags(LinearScale::ManualDiapason) ? fabs(max-min) : dataDiapason);
	x0 = (int)( plotDiapason - min*Mx );
};

void  LinearScaleY::setRefPoint( double val, double pos, double d )
{
	max = val+d*(1-pos); 
    min = max-d;
};
