#include <QPixmap>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QSizePolicy>

#include <canvas.h>

/**
 * Constructors/Destructors
 */
Canvas::Canvas(QWidget *parent, Qt::WindowFlags f):QFrame(parent,f)
{
   staticPixmap  = NULL;//new QPixmap(size());
   dynamicPixmap = NULL;//new QPixmap(size());
	
   setAttribute( Qt::WA_NoSystemBackground, true );
   setAttribute( Qt::WA_OpaquePaintEvent, true );
   
   QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
   sizePolicy.setHorizontalStretch(0);
   sizePolicy.setVerticalStretch(0);
   sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
   setSizePolicy(sizePolicy);
};
 
Canvas::~Canvas()
{
   delete staticPixmap;
   delete dynamicPixmap;
 };

/**
 * Event handlers.
 */
void Canvas::paintEvent ( QPaintEvent * event )
{
   QPainter painter(this);
   
   qWarning("\nCanvas::paintEvent: Left=%u Right=%u",event->rect().left(), event->rect().right() );
   painter.drawPixmap( event->rect(), *dynamicPixmap, event->rect() );
   painter.drawPixmap( event->rect(), *staticPixmap, event->rect() );
};

void Canvas::resizeEvent ( QResizeEvent * event )
{
	delete staticPixmap;
	delete dynamicPixmap;
		
	staticPixmap = new QPixmap( event->size() );
	staticPixmap->fill( QColor(0,0,0,0) );//fill transparency color
	
	dynamicPixmap = new QPixmap( event->size() );
	dynamicPixmap->fill( QColor(0,0,0,255) );
	
	emit sizeChanged();
};
