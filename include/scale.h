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

/**
 * Class Scale
 * Interface for all possible scales. Scale instance is responsible on
 * convert value to pixel coordinate and back to front.
 */
class PLOTTER_EXPORT Scale
{
public:
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
    * Ref point is point with the fixed position. 
    * With the help of such point You could fixed certain value on certain position.  
    * @param val data value for fixing.
    * @param pos position on canvas. For this way canvas has special size - [0;1] by Y and X scales.  
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
   
protected:
	//Minimum value that coresponds to canvas area  
	double min;
	
	//Maximum value that coresponds to canvas area
	double max;
};
#endif //SCALE_H
