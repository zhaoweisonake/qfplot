#ifndef SCALEWIDGET_H
#define SCALEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QPen>
#include <QFlags>

#include "scale.h"
#include "rect.h"

//PLOTTER_IMPORT has hi prority them PLOTTER_EXPORT
#if defined(Q_WS_WIN)
#  if !defined(PLOTTER_EXPORT) && !defined(PLOTTER_IMPORT)
#    define PLOTTER_EXPORT
#  elif defined(PLOTTER_IMPORT)
#    if defined(PLOTTER_EXPORT)
#      undef PLOTTER_EXPORT
#    endif
#    define PLOTTER_EXPORT __declspec(dllimport)
#  elif defined(PLOTTER_EXPORT)
#    undef PLOTTER_EXPORT
#    define PLOTTER_EXPORT __declspec(dllexport)
#  endif
#else
#  define PLOTTER_EXPORT
#endif

/**
 * Class ScaleWidget
 * 
 */
class PLOTTER_EXPORT ScaleWidget : public QWidget
{
	Q_OBJECT;
	
public:
   enum ScaleWidgetFlags{
	//Enables view text label of this ScaleWidget. @see setLabel()
   	ViewLabel		= 1,
   	//Enables view second points. It's point between primary points
   	ViewSecondPoint = 2,
   	//Enables numbers on scale
  	ViewNumbers		= 4,
 	//Enables line between scale and canvas
   	ViewLine		= 8,
   };
   Q_DECLARE_FLAGS(ScaleFlag, ScaleWidgetFlags);
   
   /**
    * Next four flags determines current location of ScaleWidget on Plotter.
    * @see setOrientation() for manage orientation ScaleWidget.
    */
   enum Orientation
   { 
  	Top				= 1,
  	Right			= 2,
  	Bottom			= 4,
  	Left			= 8
   };
   
    //Creates Scale widget with certain Scale
    ScaleWidget ( Scale* scale, QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~ScaleWidget(){};

protected:
   virtual void paintEvent ( QPaintEvent* event );
   void setOrientation( Orientation orientation );
   
   virtual void drawTop   (  QPainter& painter, const Rect& rect  );
   virtual void drawRight (  QPainter& painter, const Rect& rect  );
   virtual void drawBottom(  QPainter& painter, const Rect& rect  );
   virtual void drawLeft  (  QPainter& painter, const Rect& rect  );

   virtual void drawBasicPoints ( QPainter& painter, const Rect& rect );
   virtual void drawBasicNumbers( QPainter& painter, const Rect& rect );
   
   virtual void calculateMinSize();
   
   /**
    * @return true if flag f is enabled, otherwise return false
    */
   inline bool testFlags ( ScaleWidgetFlags f )
   {
   	   return flags.testFlag( f );
   };
   
private:
	ScaleFlag	flags;
    Scale*	scale;
    QLabel  label;
    
    QPen	penFirstPoint;
    QPen	penSecondPoint;
    QFont   numbersFont;
    
    //Length of line for first points
    int		firstPointLen;
    
    //Length of line for second points
    int		secondPointLen;
    
    double		firstDivision;
    double		secondDivision;
    
    //Current orientation on Plotter
    Orientation	currOrientation;
    
    void (ScaleWidget::*paintHnd)( QPainter& painter, const Rect& rect  );
};
 
#endif //SCALEWIDGET_H
