#include "rect.h"

void Rect::expand( const QPoint& point )
{
	setLeft  ( qMin(point.x(), left()  ) );
	setRight ( qMax(point.x(), right() ) );
	setTop   ( qMax(point.y(), top()   ) );
	setBottom( qMin(point.y(), bottom()) ); 
};
