#ifndef CURVE_H
#define CURVE_H

#include<QRectF> 

#include "plotitem.h"
#include "curvedata.h"
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

class CurveData;
/**
 * Class curve represent such plot item as curve.
 * 
 */
class PLOTTER_EXPORT Curve : public PlotItem
{

public:
   Curve( const QString& nm, const QString& dmn, Scale* sx=NULL, Scale* sy=NULL, CurveData* dt=NULL );
   virtual ~Curve();
   
   virtual Rect  drawFragment ( QPainter &painter, const Rect& drawRect );
   virtual const RectF& dataRect()const;
   virtual const Rect invRect();
   virtual void  clearInvRect();

protected:
   QPoint pointInInterval( const QPoint& begin, const QPoint& end, int x ) const;

private:
  
   /**
    * Maps certain rect from data dimension to rect on plotter dimension
    * @param rect source rect from data dimension
    * @return Mapped rect on plotter.
    */ 
   Rect real2plot( const RectF& rect );
   
   /**
    * Maps certain point from data dimension to plotter dimension
    * @param point source from data dimension 
    * @return 
    */
   inline QPoint real2plot( const QPointF& point )
   {
   	  return QPoint(
   	     scaleX->real2plot( point.x() ),
   	     scaleY->real2plot( point.y() ) 
   	   );
   };

   
   /**
    * Fields
    */
    QString	name;
    QString	dimension;
    CurveData*	data;
};
#endif //CURVE_H
