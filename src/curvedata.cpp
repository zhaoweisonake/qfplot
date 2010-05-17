#include <curvedata.h>

/**
 * Constructors/Destructors
 */
CurveData::CurveData(unsigned int n):ring(n)
{

};

CurveData::~CurveData()
{
	
}

/**
 * Methods
 */
void CurveData::pushBack( const QPointF& point )
{
   bool do_refine_rect = false;
   
   if( ring.size() < ring.max_size() )
   {
       rect.expand( point );
   }else{
   	do_refine_rect = ( rect.left()   == ring[0].x() ) ||
	                 ( rect.right()  == ring[0].x() ) ||
	                 ( rect.bottom() == ring[0].y() ) ||
	                 ( rect.top()    == ring[0].y() );	
   }
   
   invRect.expand( point );
   ring.push_back(point);
   
   if( do_refine_rect )
   {
   	  rect = RectF(point.x(), point.y(), point.x(), point.y());

	  for( unsigned int i=0; i<ring.size()-1;i++)
	  {
	    rect.expand( ring[i] );
	  }
   }
};

//TODO test code
#include <math.h>
#include <cstdlib>
static int i=0;
void CurveData::tsts_slot()
{
  pushBack( QPointF(i*2,10*sin((double)i/5)*rand()/RAND_MAX) );
  i++;
  if( i > 200 )
    i =0;
  //qWarning("timeout");
};
