#include <QPainter>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

#include "plotter.h" 
#include "canvas.h"
#include "scale.h"
#include "scalewidget.h"

Plotter::Plotter( Canvas *cnv, QWidget *parent, Qt::WindowFlags f):QWidget( parent , f )
{
    QHBoxLayout *hbl;
    QVBoxLayout *vbl;
    
    setBrush(Qt::lightGray);//TODO must be moved to plotter builder

    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);

    left = new QFrame(this);
    left->setFrameShape(QFrame::NoFrame);
    left->setFrameShadow(QFrame::Raised);

    gridLayout->addWidget(left, 1, 0, 1, 1);
    
    hbl = new QHBoxLayout(left);
    hbl->setSpacing(0);
    hbl->setMargin(0);

    if( cnv != NULL )
	   attachCanvas( cnv );

    right = new QFrame(this);
    right->setFrameShape(QFrame::NoFrame);
    right->setFrameShadow(QFrame::Raised);

    gridLayout->addWidget(right, 1, 2, 1, 1);
    
    hbl = new QHBoxLayout(right);
    hbl->setSpacing(0);
    hbl->setMargin(0);

    top = new QFrame(this);
    top->setFrameShape(QFrame::NoFrame);
    top->setFrameShadow(QFrame::Raised);

    gridLayout->addWidget(top, 0, 1, 1, 1);
    
    vbl = new QVBoxLayout(top);
    vbl->setSpacing(0);
    vbl->setMargin(0);

    bottom = new QFrame(this);
    bottom->setFrameShape(QFrame::NoFrame);
    bottom->setFrameShadow(QFrame::Raised);

    gridLayout->addWidget(bottom, 2, 1, 1, 1);
    
    vbl = new QVBoxLayout(bottom);
    vbl->setSpacing(0);
    vbl->setMargin(0);
    
    setLayout(gridLayout);

    //xScale = QSharedPointer<MyObject>(new MyObject, doDeleteLater);
};
 
Plotter::~Plotter()
{
	detachCanvas();
};
 
/**
 * SLOT Method
 * This method check diapason for all dynamic items and
 * draw full frame on canvas.   
 */ 
void Plotter::buildFrame( )
{
   if( canvas != NULL )
   {
      ItemList::iterator i = dynamicItems.begin();
      //TODO calculate new max_pos
      //Temporary after resizing we will draw from left side
      //max_pos = 0;
	 
      while (i != dynamicItems.end() )
      {
         (*i)->getScaleY()->changeDiapason( (*i)->dataRect().height(), canvas->height() );
	 (*i)->getScaleX()->changeDiapason( (*i)->dataRect().width(), canvas->width() );
	  i++;
      };
    }else{
       qWarning("WARNING: Plotter not contain canvas");
    };
    
    canvas->getDynamicPixmap()->fill( brush.color() );
    drawStaticItems( canvas->contentsRect()  );
    drawDynamicItems( canvas->contentsRect() );
 };

/**
 * Draws all static item.
 * @param requestRect - competent rect for drawing
 * @return rect that contains painted elements  
 */
const Rect Plotter::drawStaticItems( const Rect& requestRect )
{
   Rect      resultRect;
   
   if( canvas != NULL )
   {
   	  QPainter   painter;
   	  
   	  ItemList::iterator i = staticItems.begin();
   	   	  
   	  painter.begin( canvas->getStaticPixmap() );
	  	
	  i = staticItems.begin();
	 	
	  while (i != staticItems.end() )
	  {
		  if( resultRect.isNull() )
		     resultRect = (*i)->drawFragment( painter, requestRect );
		  else
		  	 resultRect = resultRect.united( (*i)->drawFragment( painter, requestRect ) );
		  
	     i++;
	  };
	  
	  painter.end();
 	}else{
 		 qWarning("WARNING: Plotter not contain canvas");
	};
	return resultRect;
};

/**
 * Draws all dynamic items.
 * @param requestRect - competent rect for drawing. 
 * This rect will be erased before certain item will be painted.   
 * @return rect that contains painted elements
 */
const Rect Plotter::drawDynamicItems( const Rect& requestRect )
{
   Rect      resultRect;
   
   if( canvas != NULL )
   {
      QPainter   painter;
      painter.begin( canvas->getDynamicPixmap() );
      painter.setRenderHint(QPainter::Antialiasing, true);

      ItemList::iterator i = dynamicItems.begin();
      while (i != dynamicItems.end() )
      {
         if( resultRect.isNull() )
	    resultRect = (*i)->drawFragment( painter, requestRect );
	 else
	   resultRect = resultRect.united( (*i)->drawFragment( painter, requestRect ) );

         i++;
      };
      painter.end();
   }else{
      qWarning("WARNING: Plotter not contain canvas");
   };
   return resultRect;
};

/**
 * SLOT Method
 * Draw only new data on the plotter
 */
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

/**
 * Attaches canvas
 */
void Plotter::attachCanvas( Canvas *cnv )
{
   canvas = cnv;
   gridLayout->addWidget(canvas, 1, 1, 1, 1);
   connect( canvas, SIGNAL(sizeChanged()), this, SLOT(buildFrame()) );
};

/**
 * Detasches canvas
 */
Canvas* Plotter::detachCanvas()
{
   	  gridLayout->removeWidget( canvas );
   	  canvas->setParent(0);
   	  disconnect( this, SLOT(buildFrame()) );
   	  return canvas;
};

ScaleWidget*  Plotter::createXScale( Scale* s )
{
	ScaleWidget *sw = new ScaleWidget( s, left);
	
	XScales.append(sw);
	left->layout()->addWidget( sw );
	
	return sw;
};
