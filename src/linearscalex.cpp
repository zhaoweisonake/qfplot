#include "linearscalex.h"
#include <math.h>
/**
 * Constructors/Destructors
 */
/**
 * Methods
 */
void LinearScaleX::changeDiapason (double dataDiapason, double plotDiapason)
{
	Mx = plotDiapason/(testFlags(LinearScale::ManualDiapason) ? fabs(max-min) : dataDiapason);
        //Calculate x0 in the intention what data value 0 is corresponded to 0 plot plot position.
	x0 = static_cast<int>(-min*Mx );
};

void LinearScaleX::setRefPoint( double val, double pos, double d )
{
	x0 = static_cast<int>( val - pos*Mx );
};
