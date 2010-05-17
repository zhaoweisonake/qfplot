#include <QPainter>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QMouseEvent>

#include "plotter.h" 
#include "canvas.h"
#include "scale.h"
#include "scalewidget.h"
#include "linearscalex.h"
#include "linearscaley.h"

Plotter::Plotter( CanvasPtr cnv, QWidget *parent, Qt::WindowFlags f):QWidget( parent, f )
{
   QHBoxLayout *hbl;
   QVBoxLayout *vbl;

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

   if( cnv.isNull() )
   {
       cnv = CanvasPtr( new Canvas() );
   }
	attachCanvas( cnv );

   if( currentXScale.isNull() )
   {
      currentXScale = ScalePtr( new LinearScaleX() );
   };

   if( currentYScale.isNull() )
   {
      currentYScale = ScalePtr( new LinearScaleY() );
   };

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

   setBrush(Qt::lightGray);//TODO must be moved to plotter builder
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
 * Attaches canvas
 */
void Plotter::attachCanvas( CanvasPtr cnv )
{
   canvas = cnv;
   gridLayout->addWidget(canvas.data(), 1, 1, 1, 1);
   connect( canvas.data(), SIGNAL(sizeChanged()), this, SLOT(buildFrame()) );
   canvas->installEventFilter(this);
   canvas->setFocus();
};

/**
 * Detasches canvas
 */
CanvasPtr Plotter::detachCanvas()
{
   canvas->removeEventFilter(this);
   disconnect( this, SLOT(buildFrame()) );
   gridLayout->removeWidget( canvas.data() );
   canvas->setParent(0);
   return canvas;
};

bool Plotter::eventFilter(QObject *obj, QEvent *event)
{
   if( event->type() == QEvent::MouseMove )
   {
      qWarning("Move"); return true;
      //return this->MouseMove( obj, static_cast<QMouseEvent *>(event));
   }

   //qWarning("Cought Event %d",event->type());
   // standard event processing
   return QObject::eventFilter(obj, event);
}

void Plotter::keyPressEvent( QKeyEvent *event )
{
	 qWarning("Press %d", event->key());
}

void Plotter::keyReleaseEvent( QKeyEvent *event )
{
    if(event->key() == Qt::Key_Equal)
    {
       qWarning("Increase zoom 0.1");
       
    }
    if(event->key() == Qt::Key_Minus)
    {
       qWarning("Decrease zoom 0.1");
    }
}
