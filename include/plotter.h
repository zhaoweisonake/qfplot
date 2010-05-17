#ifndef PLOTTER_H
#define PLOTTER_H

#include <QSharedPointer>
#include <QList>
#include <QBrush>
#include <QWidget>
#include <QKeyEvent>

#include "plotitem.h"
#include "rect.h"
#include "rectf.h"
#include "scale.h"
#include "canvas.h"

class QFrame;
class QGridLayout;

class PlotItem;
class PlotItems;
class ScaleWidget;
class LinearScaleX;

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
 * Class Plotter is a widget that contains curves, scales, grids and other items
 * these derived from PlotItem. 
 * The central part of the widget is drawing area. On borders are placed scale widgets.
 * This class isn't be able to provide quick redraw. 
 */
class PLOTTER_EXPORT Plotter : public QWidget
{
   Q_OBJECT;

public:
  /**
   * Constructors
   */
   Plotter( CanvasPtr cnv, QWidget *parent = 0, Qt::WindowFlags f = 0 );
   virtual ~Plotter();

   /**
    * Sets custom brush for fill background
    * @param brush Brush for filling background 
    */
   void setBrush( const QBrush & brush )
   {
      this->brush = brush;
   };
   
   /**
    * Sets the brush with given color and style. 
    * By default style is solid pattern. 
    * @param color color. @see QColor
    * @param style @see Qt::BrushStyle. It describes fill style. 
    */
   inline void setBrush ( QColor &color, Qt::BrushStyle style = Qt::SolidPattern )
   {
   	  setBrush( QBrush( color, style ) );
   };
   
   void attachCanvas( CanvasPtr cnv );
   
   CanvasPtr  detachCanvas();
       
   /**
    * Operations
    */
    inline void attachStaticItem( PlotItem* item )
    {
    	staticItems.append( item );
    };
    
    inline void attachDynamicItem( PlotItem* item )
    {
    	dynamicItems.append( item );
    };

    inline ScalePtr xScale()
    { return currentXScale; };

    inline ScalePtr yScale()
    { return currentYScale; };

    //LinearScaleX	*xScale;//TODO delete it

public slots:
   /**
    * Draw all items. It should call when canvas change size.
    */
   void buildFrame();
   
protected:
   virtual bool eventFilter(QObject *obj, QEvent *event);

   /**
   * drawStaticItems draws all static items inside rectangle that is defined by argumen requestRect.
   * It isn't the same as drawing on the screen! All plotter changes will be saved inside own canvas.
   * A Plotter instance uses canvas as cache. 
   */
   const Rect drawStaticItems ( const Rect& requestRect );

   virtual void keyPressEvent( QKeyEvent *event);

   virtual void keyReleaseEvent( QKeyEvent *event);

   /**
   * This method corresponds to drawStaticItems but it draws all dynamic items.
   */
   const Rect drawDynamicItems( const Rect& requestRect );

   typedef QList<PlotItem*> ItemList;
   
   ItemList   staticItems;
   ItemList   dynamicItems;
   //ItemList   onScreenItems; //TODO for future

   ScalePtr  currentXScale;
   ScalePtr  currentYScale;

private:
   QBrush brush;  //for background

   CanvasPtr canvas;
   QGridLayout *gridLayout;
   
   QFrame *left;
   QFrame *right;
   QFrame *top;
   QFrame *bottom;
};
#endif //PLOTTER_H
