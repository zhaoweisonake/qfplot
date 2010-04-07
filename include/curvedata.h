#ifndef CURVEDATA_H
#define CURVEDATA_H

#include <QObject>

#include "ring.h"
#include "rectf.h"

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
 * Class CurveData
 * Storage for data. 
 */
class PLOTTER_EXPORT CurveData :  public QObject
{
   Q_OBJECT
public:
   /**
    * Constructors
    */
   CurveData(unsigned int n);
   ~CurveData();
   
   /**
    * Operations
    */
   inline QPointF& point( int i )
   {
   	  return ring[i];
   }
   
   inline unsigned int size()const
   {
   	  return ring.size(); 
   };
   
   void pushBack( const QPointF& point );
   
   /**
    * 
    */
   inline const RectF& dataRect() const
   {
   	  return rect; 
   }
   
   inline void clearInvRect()
   {
   	  invRect = RectF( ring[size()-1].x(), ring[size()-1].y(), 0, 0 );
   };
   
   inline const RectF& invalidateRect()const
   {
   	  return invRect;
   } 
   
public slots:   
   void tsts_slot(); 
   
private:
 
    //Storage for our data.
    Ring< QPointF >	ring;
    
    //Current rect for our data.
    RectF	rect;
    
    //Current rect with invalidate area
    RectF  invRect;
};
#endif //CURVEDATA_H

