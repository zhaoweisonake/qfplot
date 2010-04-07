#ifndef CANVAS_H
#define CANVAS_H

#include <QFrame>

class QPixmap;
class QResizeEvent;
class QPaintEvent;
 
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
 * Class Canvas provide cache pixmaps for drawing curves, axis, grid and othe items.
 * Not changed plotter items should draw on static pixmap. Changed plotter items
 * should draw on dynamic pixmap. Static pixmap always has transparent background.
 * Dynamic pixmap has plotter background.
 */
class PLOTTER_EXPORT Canvas : public QFrame
{
	Q_OBJECT;
	
public:
    Canvas(QWidget *parent = 0, Qt::WindowFlags f = 0 );
    ~Canvas();
   
   //@return Returns pointer on pixmap for static items.
   inline QPixmap*  getStaticPixmap ()
   {
      return staticPixmap;
   };
   
   //@return Returns pointer on pixmap for dynamic items.
   inline QPixmap*  getDynamicPixmap ()
   {
      return dynamicPixmap;
   };
   
signals:
	/**
	 * It will emit if canvas change size.
	 * Owner plotter should catch it for build new frame. 
	 */
	void sizeChanged(); 

protected:
   /**
    * Handler for resize event. It call if canvas changed size.
    * @param event pointer on specific event information. See Qt documentation
    */   
   void  resizeEvent (QResizeEvent* event);
   
   /**
    * Handler for paint event. It will call if to be needed repaint part of canvas
    * @param event pointer on specific event information. See Qt documentation.
    */
   void  paintEvent (QPaintEvent* event);
   
private:
    QPixmap* staticPixmap;
    QPixmap* dynamicPixmap;
};
#endif //CANVAS_H


