#ifndef LINEARSCALEX_H
#define LINEARSCALEX_H

#include "linearscale.h"

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
class PLOTTER_EXPORT LinearScaleX : public LinearScale
{

public:
   virtual void changeDiapason (double dataDiapason, double plotDiapason);
   virtual void setRefPoint( double val, double pos, double d );
};
#endif //LINEARSCALEX_H
