#ifndef GRID_H
#define GRID_H

#include<plotitem.h> 

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
 * Class Grid
 * 
 */
class PLOTTER_EXPORT Grid : public PlotItem
{
public:
   Grid( int xc=10, int yc=10 );
   virtual ~Grid();
   
   virtual Rect  drawFragment ( QPainter &painter, const Rect& drawRect );
   virtual const RectF& dataRect()const;
   virtual const Rect invRect();
   virtual void  clearInvRect();

private:
    int xcount;
    int ycount;
};
#endif //GRID_H
