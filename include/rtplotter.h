#ifndef RTPLOTTER_H
#define RTPLOTTER_H

#include "plotter.h"

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
 * Class RTPlotter
 * Perfomance plotter with one X scale that is mean time.
 * All curves are updated incrementaly from left to right.
 */
class PLOTTER_EXPORT RTPlotter : public Plotter
{
   Q_OBJECT;
   Q_PROPERTY(double diapason READ diapason WRITE setDiapason);

public:
  /**
   * Constructors
   */
   RTPlotter( Canvas *cnv = 0, QWidget *parent = 0, Qt::WindowFlags f = 0 );
   ~RTPlotter();

   /**
   * Returns Pointer on the X-scale.
   * @return returns pointer on X-Scale
   */
   inline Scale *xScale( void )
   {
      return XScale;
   };
  
public slots:
   /**
    * Draw all items. It should call when canvas change size.
    */
   void buildFrame();
   
   /**
    * Draw new data for all dynamic items and repaint changed area on canvas.
    */
   void drawNewData();

    void setDiapason(double diapason);
    double diapason() const;
   
protected:
//Nothing
  
private:
   //X-Scale must be one since it is correspond to real time.
   Scale* XScale;

   //X diapason
   double XDiapason;

 };
#endif //RTPLOTTER_H
