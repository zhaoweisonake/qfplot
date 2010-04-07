
#include <math.h>
#include <rtlinearscalex.h>


void RTLinearScaleX::setRefPoint( double val, double pos, double d )
{
};

int RTLinearScaleX::real2plot (double value)const
{
  int x, tmp = x0;

  //x0 += ( fmod(value,max-min) )? currentX-diapason  : currentX ;

  /*The next string was duplicated 
    from the LinearScale::real2plot by perfomance reason.
   */
  x = static_cast<int>(value*Mx+x0);
  //x0 = tmp;
  return x;
};

double RTLinearScaleX::plot2real (double value)const
{
  return -1;
};
