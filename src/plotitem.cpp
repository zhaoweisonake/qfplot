#include "plotitem.h"


/**
 * Constructors/Destructors
 */
PlotItem::PlotItem()
{
	pen.setWidth(5);
	pen.setColor(Qt::red);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
}; 
