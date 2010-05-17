#include <QPainter>
#include <QPaintEvent>
#include <QtGlobal>
#include <QFontMetrics>
#include <QMatrix>

#include "scalewidget.h"

/**
 * Constructors/Destructors
 */
 ScaleWidget::ScaleWidget ( Scale* sc, QWidget * parent, Qt::WindowFlags f ) 
 :QWidget( parent, f ),
 flags(0)
 {
 	scale = sc;
 	
 	//setMinimumSize( QSize(0,30) );
 	
 	 firstPointLen  = 15;
    secondPointLen = 7;
    
    firstDivision = 20;
    secondDivision = 4;
    
    flags |= ViewNumbers;
    flags |= ViewSecondPoint;
    flags |= ViewLine;
   
    setOrientation( Left );
    calculateMinSize();
    
};
/**
 * Methods
 */
void ScaleWidget::drawBasicPoints( QPainter& painter, const Rect& rect )
{
	painter.setPen(penFirstPoint);
	
	if( testFlags( ViewLine ) )
		painter.drawLine(0, penFirstPoint.width()/2, rect.width(), penFirstPoint.width()/2 );
	
	int x;
	double i = scale->minValue();
	
	for( x = scale->real2plot(i); i <= scale->maxValue(); x = scale->real2plot(i += firstDivision) )
	{
		qWarning("x=%i",x);
		painter.drawLine( x, 0, x, firstPointLen);
	}
	
	if( testFlags( ViewSecondPoint ) )
	{
	   painter.setPen(penSecondPoint);
	   i = scale->minValue();
       for( x = scale->real2plot(i); i <= scale->maxValue(); x = scale->real2plot(i += secondDivision) )
		  painter.drawLine(x, 0, x, secondPointLen);
	}
};

void ScaleWidget::drawBasicNumbers( QPainter& painter,  const Rect& rect )
{
	QFontMetrics	fmetrics( numbersFont );
	int x, fontHeight = fmetrics.height();
	double i = scale->minValue();
	
	painter.setFont( numbersFont );
	
	//draw first number with the special offset
	x = scale->real2plot( i );
    painter.drawText( x, firstPointLen+fmetrics.height(), QString::number( i ) );		
    
	for( i+=firstDivision; i <= scale->maxValue(); i += firstDivision )
	{
		x = scale->real2plot( i );
		x = (x>=rect.width()-1)? x-fmetrics.width(QString::number(i)) : x-fmetrics.width(QString::number(i))/2;
		painter.drawText(x, firstPointLen+fontHeight, QString::number(i) );
	}
};

void  ScaleWidget::paintEvent (QPaintEvent* event)
{
   QPainter painter(this);
   
   (this->*paintHnd)( painter, contentsRect() );
};

void ScaleWidget::calculateMinSize()
{
	int height = firstPointLen;
	
	if( testFlags( ViewSecondPoint ) )
		height = qMax( height, secondPointLen );
	
	if( testFlags( ViewNumbers ) )
	{
		QFontMetrics	fmetrics( numbersFont );
		
		height += fmetrics.height()+3;
	}
	
	if( (currOrientation ==  Top) | (currOrientation == Bottom) )
	  setMinimumSize( QSize( 0, height ) );
	else
	  setMinimumSize( QSize( height, 0 ) );
};

void ScaleWidget::setOrientation( Orientation orientation )
{
	switch( orientation )
	{
	case Top:
		paintHnd = &ScaleWidget::drawTop;
		
		break;
		
	case Right:
		paintHnd = &ScaleWidget::drawRight;
		break;
		
	case Bottom:
		paintHnd = &ScaleWidget::drawBottom;
		break;
		
	case Left:
		paintHnd = &ScaleWidget::drawLeft;
		break;
		
	default:
		qDebug("ScaleWidget::setOrientation unknown orientation");
	};
	currOrientation = orientation; 
};

void ScaleWidget::drawTop   (  QPainter& painter, const Rect& rect  )
{
	painter.save();
	painter.rotate( 180 );
	painter.translate( 1-rect.width(), 1-rect.height() );
	drawBasicPoints ( painter, rect );
	
	painter.restore();
	painter.translate(0, -firstPointLen);
	if( testFlags(ViewNumbers) )
	{
	   drawBasicNumbers( painter, rect );
	};
};
	
void ScaleWidget::drawRight (  QPainter& painter, const Rect& rect  )
{
	painter.save();
	painter.translate( 0, height()-1 );
	painter.rotate( 270 );
	QRect rc = rect;
	rc = painter.worldMatrix().mapRect( rect );
	drawBasicPoints ( painter, rc );
	painter.restore();
	
	if( testFlags(ViewNumbers) )
	{
		painter.translate( width()+firstPointLen, 0 );
		painter.rotate(90);
		rc = painter.worldMatrix().mapRect( rect );
		drawBasicNumbers( painter, rc );
	};
};

void ScaleWidget::drawBottom(  QPainter& painter, const Rect& rect  )
{
	drawBasicPoints ( painter, rect );
	
	if( testFlags(ViewNumbers) )
		drawBasicNumbers( painter, rect );
};

void ScaleWidget::drawLeft  (  QPainter& painter, const Rect& rect  )
{
	painter.save();
	painter.translate( width()-1, 0 );
	painter.rotate( 90 );
	QRect rc = rect;
    rc = painter.worldMatrix().mapRect( rect );
	drawBasicPoints ( painter, rc );
	
	if( testFlags(ViewNumbers) )
		drawBasicNumbers( painter, rc );
	
	painter.restore();
};
