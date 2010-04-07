#ifndef LINEARSCALE_H
#define LINEARSCALE_H

#include <QtGlobal>
#include <QFlags>
#include "scale.h"

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
 * Class LinearScale
 * Basic abstract class for linear scale. It's needed becouse Y-scale has invert direction.
 */
class PLOTTER_EXPORT LinearScale : public Scale
{
public:
   enum ScaleFlags
   {
      /* Diapason for data processing shall set manually*/
      ManualDiapason		= 1,
      /*
       *For scaling will be used a scpecial reference point. 
       *This point has a steel position on the plotter
       */
      UseRefPoint		= 2
   };
   Q_DECLARE_FLAGS(ScaleFlag, ScaleFlags);
	   
   LinearScale();
   virtual int     real2plot (double value)const;
   virtual double  plot2real (double value)const;
   
   void setManualDiapason( double low, double hi);
   
   inline ScaleFlag setFlags( ScaleFlags f )
   {
	   return flags |= f;
   };
   
   inline bool testFlags ( ScaleFlags f )
   {
	   return flags.testFlag( f );
   };
   
  
protected:
    ScaleFlag	flags;
    
    //zoom-factor
    double Mx;
    
    //Offset. Only x0 and Mx just use for real2plot and plot2real.
    int x0;
};
#endif //LINEARSCALE_H
