#ifndef SCALE_H
#define SCALE_H

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

#include <QSharedPointer>

class Scale;
//Shared pointer type.
typedef QSharedPointer<Scale>  ScalePtr;

/**
 * Class Scale isn`t visual element. 
 * This class translates coordinates of curve element to
 * onscreen coordinate and back to front. 
 * It is a base class for all possible scales. 
 * There are two methods for coordinates processing. These are:
 *	- plot2real
 *	- real2plot
 *
 * All other are tuning method.
 * Every Scale class provides inteligent mechanism for automatic tunning.
 * There aren't fixed owner of every scale instance. Therefore there is a ScalePtr type
 * that is a shared pointer @see QSharedPointer. It is more usefull. 
 */
class PLOTTER_EXPORT Scale
{
public:
   enum ScaleFlags
   {
      /* Diapason for data processing shall set manually*/
      ManualDiapason		= 1,
      /*
       *For scaling will be used a scpecial reference point. 
       *This point has a steel position on the plotter
       */
      UseRefPoint		= 2
   };
   Q_DECLARE_FLAGS(ScaleFlag, ScaleFlags);

   /**
    * Returns position on canvas by value
    * @param val is real value from curve data
    */
   virtual int  real2plot (double val) const = 0;
   
   /**
    * Returns value by position on canvas
    * @param val is position on a canvas.
    */
   virtual double  plot2real (double val) const = 0;
  
   /**
    * It should be called if changed data diapason or plotter diapason. 
    * @param dataDiapason - New diapason of data 
    * @param plotDiapason - New diapason of plotter.
    *        It's the same that width for XScale or height for YScale. 
    */
   virtual void  changeDiapason (double dataDiapason, double plotDiapason) = 0;
   
   /**
    *
    */
   void setManualDiapason( double low, double hi ); 

   /**
    * Ref point is point with the fixed position. 
    * With the help of such point You could fixed certain value on certain position.  
    * @param val data value for fixing.
    * @param pos position on canvas. For this case canvas has special size - [0;1] by Y and X scales.  
    */
   virtual void  setRefPoint (double val, double pos, double d) = 0;
   
   /**
    * @return minimum value for data.
    */
   inline double minValue()
   {
	   return min;
   };
   
   /**
    * @return maximum value for data.
    */
   inline double maxValue()
   {
      return max;
   };

   inline ScaleFlag setFlags( ScaleFlags f )
   {
	   return flags |= f;
   };
   
   inline bool testFlags ( ScaleFlags f )
   {
	   return flags.testFlag( f );
   };
   
   /**
    * Auxilary method. It change zoom of scale instance on factor percent
    * @param factor must be in diapason [-1;1]. Positive value means increasing zoom
    * Negative value means decreasing zoom. The value is multiplier for current zoom.
   */
   //inline setZoom( double factor)
  // {
		//  changeDiapason( max-min, )
   //};

protected:
   ScaleFlag	flags;

	//Minimum value that coresponds to canvas area  
	double min;
	
	//Maximum value that coresponds to canvas area
	double max;
};
#endif //SCALE_H
