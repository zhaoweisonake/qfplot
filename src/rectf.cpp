#include "rectf.h"

void RectF::expand(const QPointF& point )
{
	setLeft  ( qMin(point.x(), left()  ) );
	setRight ( qMax(point.x(), right() ) );
	setBottom( qMin(point.y(), bottom()) ); 
	setTop   ( qMax(point.y(), top()   ) );
};
