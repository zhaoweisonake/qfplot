
#include "rtplotter.h"
#include "linearscalex.h"  

RTPlotter::RTPlotter( Canvas *cnv, QWidget *parent, Qt::WindowFlags f ):Plotter( cnv, parent, f )
{
    XScale = new LinearScaleX();
};

RTPlotter::~RTPlotter()
{
    delete XScale;
};

void RTPlotter::buildFrame()
{
    //Plotter::buildFrame();
};
   
void RTPlotter::drawNewData()
{
    double right_value=0;
    ItemList::iterator i = dynamicItems.begin();
    while (i != dynamicItems.end() )
    {
        right_value = qMax( right_value, (*i)->dataRect().right() );
        i++;
    };

    //Upadate reference point for X-scales since plot always must contain fresh data.
    //XScale->setRefPoint( , , 0);
    //fmod(right_value,XDiapason);
    
    //Plotter::drawNewData();
};


/**
 * SLOT Method
 * Draw only new data on the plotter
 *//*
void Plotter::drawNewData()
{
   Rect clearRect;
   int max_pen_width = 0;
 
   if( canvas != NULL )
   {
      QPainter   painter;
      painter.begin( canvas->getDynamicPixmap() );
      painter.setRenderHint(QPainter::Antialiasing, true);

      ItemList::iterator i = dynamicItems.begin(); 
      while (i != dynamicItems.end() )
      { 
         //Update scales for all items.
         (*i)->getScaleY()->changeDiapason( (*i)->dataRect().height(), canvas->height() );
	      (*i)->getScaleX()->changeDiapason( (*i)->dataRect().width(), canvas->width() );
         
         //Update max_pen_width.  
         max_pen_width = qMax( max_pen_width, (*i)->Pen().width() );
 
         //Calculate rectangle that must be erased before drawing.
         if( clearRect.isNull() )
	    clearRect = (*i)->invRect();
	 else
         {
            //The Rect::united isn't applicable here.
            clearRect.setRight( qMax( clearRect.right(), (*i)->invRect().right() ) );
            clearRect.setLeft( qMax( clearRect.left(), (*i)->invRect().left() ) );
         }
	 i++;
      };

      //We don't know vertical range of new data, so clear maximum vertical range 
      clearRect.setY(0);
      clearRect.setHeight( canvas->height() );

      //Tune erase area for curves width
      clearRect.setWidth( clearRect.width() + max_pen_width );//TODO add gap
      clearRect.setLeft( clearRect.left() + max_pen_width/2 );

      //Erase area
      painter.fillRect( clearRect, brush );

      //Draw all dynamic items.
      i = dynamicItems.begin();
      while (i != dynamicItems.end() )
      { 
         (*i)->drawFragment( painter, (*i)->invRect() );
	 (*i)->clearInvRect();
	 i++;
      };
   }else{
      qWarning("WARNING: Plotter not contain canvas");
   };

   clearRect.setLeft( clearRect.left() - max_pen_width );
   canvas->repaint( clearRect );
};
*/

void RTPlotter::setDiapason(double diapason)
{
    XDiapason = diapason;
};

double RTPlotter::diapason() const
{
    return XDiapason;
};
