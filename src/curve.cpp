#include <QtGlobal>
#include <QString>
#include <QPen>
#include <QPainter>

#include <curve.h>
#include <curvedata.h>
#include <linearscalex.h>
#include <linearscaley.h>

/**
 * Constructors/Destructors
 */
Curve::Curve( const QString& nm, const QString& dmn, Scale* sx, Scale* sy, CurveData* dt )
   :name(nm),dimension(dmn)
{
	scaleX = (sx == NULL) ? new LinearScaleX() : sx ;
	scaleY = (sy == NULL) ? new LinearScaleY() : sy ;
	
    data = dt == NULL ? new CurveData(1000) : dt ; 		
};

Curve::~Curve()
{
};


Rect Curve::drawFragment ( QPainter &painter, const Rect& drawRect )
{
	Rect	rect;
	
	painter.setPen( pen );
	
	if( data->size() > 2 )
	{
           QPoint  p1,p2;
           int	   i = data->size()-1;

          //all point aren't inside rect must be passed       
          if((drawRect.width() != 0) && (drawRect.height() != 0))
          {
            //Finf a first point in the drawing area
             while( !drawRect.contains( real2plot(data->point(i)) ) )
               --i;

             if( i != data->size()-1 )
             {
                 QPoint firstPoint = pointInInterval( real2plot( data->point(i+1) ), p1 = real2plot( data->point(i) ), drawRect.right() );
                 painter.drawLine( p1,  firstPoint );
                 rect = Rect( drawRect.right(), p1.y(), 0, 0 );
             };
                     
          }else{
             return Rect();//Nothing for drawing. retrurn null rect.
          }
       
          p1 = real2plot( data->point(i) );
          rect = Rect( p1.x(), p1.y(), 0, 0 );
          //Draw lines 
          for( ; i >= 0; i--, p1=p2 )
          {
             p2 = real2plot( data->point(i) );
             if( p2.x() < drawRect.left() )
             {
                  break;
             }
             painter.drawLine( p1, p2 );
	     rect.expand( p2 );
          };
       }; 

    return rect.normalized();
};

const Rect Curve::invRect()
{
	return real2plot( data->invalidateRect() );
};

void Curve::clearInvRect()
{
        qWarning("data=%p\n",data);
	data->clearInvRect();
};

const RectF& Curve::dataRect()const
{
	return data->dataRect();
};

Rect Curve::real2plot( const RectF& rt )
{
	Rect rect;
	
	rect.setLeft  ( scaleX->real2plot( rt.left()   ) );
	rect.setTop   ( scaleY->real2plot( rt.top()    ) );
	rect.setRight ( scaleX->real2plot( rt.right()  ) );
	rect.setBottom( scaleY->real2plot( rt.bottom() ) );

	return rect;
};

QPoint Curve::pointInInterval( const QPoint& begin, const QPoint& end, int x ) const
{
    int k = (end.y()-begin.y())/(end.x()-begin.x());
    int b = begin.y() - k*begin.x();
    int y = k*x+b;

    return QPoint( x, y );
};