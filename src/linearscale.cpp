
#include <linearscale.h>

LinearScale::LinearScale()
{
	flags = 0;
}
/**
 * Methods
 */ 
 
double LinearScale::plot2real(double val)const
{
	return (val-x0)/Mx;
};

int LinearScale::real2plot(double val)const
{
	return static_cast<int>(val*Mx+x0);
};

void LinearScale::setManualDiapason( double low, double hi )
{
	if( !testFlags( LinearScale::ManualDiapason) )
		qWarning("LinearScale::setManualDiapason - LinearScale::ManualDiapason is false. Await strange behavior");
	
	min = low;
	max = hi;
};
