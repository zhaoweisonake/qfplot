#ifndef RTLINEARSCALEX_H
#define RTLINEARSCALEX_H

#include "linearscalex.h"

//PLOTTER_IMPORT has hi prority them PLOTTER_EXPORT
#if defined(Q_WS_WIN)
#  if !defined(PLOTTER_EXPORT) && !defined(PLOTTER_IMPORT)
#    define PLOTTER_EXPORT
#  elif defined(PLOTTER_IMPORT)
#    if defined(PLOTTER_EXPORT)
#      undef PLOTTER_EXPORT
#    endif
#    define PLOTTER_EXPORT __declspec(dllimport)
#  elif defined(PLOTTER_EXPORT)
#    undef PLOTTER_EXPORT
#    define PLOTTER_EXPORT __declspec(dllexport)
#  endif
#else
#  define PLOTTER_EXPORT
#endif

/**
 * Class LinearScaleX
 * 
 */
class PLOTTER_EXPORT RTLinearScaleX : public LinearScaleX
{

public:
   //Must be called after change time on a plotter.
   virtual void setRefPoint( double val, double pos, double d );

   virtual int     real2plot (double value)const;
   virtual double  plot2real (double value)const;

protected:
   //Max value on a plotter.
   double currentVal;

   //Corresponded position of the currentVal.
   double currentX; 
};
#endif //RTLINEARSCALEX_H
