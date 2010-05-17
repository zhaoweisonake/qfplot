#include <QtGlobal>
#include <QPainter>

#include <grid.h>
#include <rectf.h>
#include <rect.h>

Grid::Grid( int xc, int yc )
{
  xcount = xc;
  ycount = yc;

  pen = QPen();
};

Grid::~Grid()
{
//nothing to do
};
   
Rect  Grid::drawFragment ( QPainter &painter, const Rect& drawRect )
{
   int i;

   painter.setPen( pen );

   for( i=0; i<=xcount; i++ )
   {
      int x = i*drawRect.width()/xcount;
      painter.drawLine( x,0,x,drawRect.height() );
   };

   for( i=0; i<=ycount; i++ )
   {
      int y = i*drawRect.height()/ycount;
      painter.drawLine( 0, y, drawRect.width(), y );
   };

   return drawRect;
};

const RectF& Grid::dataRect()const
{
   static RectF rect;
   return rect;
};

const Rect Grid::invRect()
{
//nothing to do
   return Rect();
};

void  Grid::clearInvRect()
{
//nothing to do
};

