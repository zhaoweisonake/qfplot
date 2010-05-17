#ifndef PLOTITEM_H
#define PLOTITEM_H

#include <QObject>
#include <QPen>
#include <QRect>
#include <QPainter>

#include "rect.h"
#include "rectf.h"
#include "scale.h"

class CurveData;

/**
 * Class PlotItem
 * It's basic abstract class that represent all posible visual elements on plotter area. 
 */
class PlotItem 
{
public:
   /**
    * Constructors
    */
   PlotItem();
   virtual ~PlotItem(){};
   /**
    * Operations
    */

   /**
    * 
    */
    inline void setPen( QPen& pen )
    {
        this->pen = pen;
    };

   /**
    * 
    */
    inline void setPen( Qt::PenStyle style )
    {
       QPen pen(style);
       setPen( pen );
    };

   /**
    * 
    */
   inline void setPen(const QColor &color)
   {
       QPen pen(color);
       setPen( pen );
   };

   /**
    * 
    */
    inline const QPen& Pen() const
    {
       return this->pen;
    };
    
   /**
    * 
    */
   inline ScalePtr  getScaleX () const
   {
   	  return scaleX;
   };
   
   /**
    * 
    */
   ScalePtr  getScaleY ()const
   {
   	  return scaleY;
   };
      
   /**
    * 
    * @param scale 
    */
   void  setScaleX (ScalePtr scale);
      
   
   /**
    * 
    * @param scale 
    */
   void  setScaleY (ScalePtr scale);
      
   virtual const Rect invRect()=0;
   
   virtual void clearInvRect()=0;
      
  /**
   * Draws his fragment into certain rect.
   * @param painter painter for drawing.
   * @param drawRect this rect could be filled. Don't fill canvas area outside!
   * @return Real filled rect.
   */
   virtual Rect drawFragment (QPainter &painter, const Rect& drawRect )= 0;
   
   virtual const RectF& dataRect()const=0;
      
protected:
    QPen 	   pen;
    ScalePtr 	scaleX;
    ScalePtr 	scaleY;
};
#endif //PLOTITEM_H
