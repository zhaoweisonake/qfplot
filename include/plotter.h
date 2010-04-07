#ifndef PLOTTER_H
#define PLOTTER_H


#include <QPen>
#include <QBrush>
#include <QList>
#include <QWidget>

#include "plotitem.h"
#include "rect.h"
#include "rectf.h"

class QFrame;
class QGridLayout;

class PlotItem;
class Canvas;
class PlotItems;
class ScaleWidget;

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
 * Class Plotter
 * Basic class for mantaining all plot items, axis, scales, grids and so on.
 * The main widget of plotter is Canvas. A canvas represents the draving area of the plotter.
 */
class PLOTTER_EXPORT Plotter : public QWidget
{
   Q_OBJECT;

public:
  /**
   * Constructors
   */
   Plotter( Canvas *cnv = 0, QWidget *parent = 0, Qt::WindowFlags f = 0 );
   ~Plotter();

  /**
   * Accessor Methods
   */
   inline void setPen( const QPen & pen )
   {
      this->pen = pen;
   };
   
   inline void setPen(const QColor &color)
   {
   	  setPen( QPen( color ) );
   };
   
   inline void setPen ( Qt::PenStyle style )
   {
   	  setPen( QPen( style ) );
   };

   void setBrush( const QBrush & brush )
   {
      this->brush = brush;
   };
   
   inline void setBrush ( Qt::BrushStyle style )
   {
   	  setBrush( QBrush( style ) );
   };
   
   void attachCanvas( Canvas *cnv );
   
   Canvas*  detachCanvas();
       
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
    
    ScaleWidget* createXScale( Scale* s);
  
public slots:
   /**
    * Draw all items. It should call wheb canvas change size.
    */
   void buildFrame();
   
   /**
    * Draw new data for all dynamic items and repaint changed area on canvas.
    */
   void drawNewData();
   
protected:
   /**
   * drawStaticItems draws all static items inside rectangle that is defined by argumen requestRect.
   * It isn't the same as drawing on the screen! All plotter changes will be saved inside own canvas.
   * A Plotter instance uses canvas as cache. 
   */
   const Rect drawStaticItems ( const Rect& requestRect );

   /**
   * This method corresponds to drawStaticItems but it draws all dynamic items.
   */
   const Rect drawDynamicItems( const Rect& requestRect );

   /**
   * @return returns rect that must be erased for new parts of dynamic items.
   */
   //const Rect clearRect( void );

   typedef QList<PlotItem*> ItemList;
   
   ItemList   staticItems;
   ItemList   dynamicItems;
   ItemList   onScreenItems; //TODO for future

private:

   QList<ScaleWidget*> YScales;
   QList<ScaleWidget*> XScales;

   QPen pen;
   QBrush brush;
   
   Canvas* canvas;
   QGridLayout *gridLayout;
   
   QFrame *left;
   QFrame *right;
   QFrame *top;
   QFrame *bottom;
};
#endif //PLOTTER_H
