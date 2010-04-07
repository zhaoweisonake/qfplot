#ifndef RECT_H_
#define RECT_H_

#include <QRect>

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

class PLOTTER_EXPORT Rect : public QRect
{
	public:
	inline Rect ()
	:QRect(){};
	
    inline Rect ( const QPoint & topLeft, const QPoint & bottomRight )
    : QRect ( topLeft, bottomRight ){};
    
    inline Rect ( const QPoint & topLeft, const QSize & size )
    : QRect ( topLeft, size ){};
    
    inline Rect ( int x, int y, int width, int height )
    :QRect ( x, y, width, height ){};
    
    inline Rect ( const QRect & rectangle )
    :QRect ( rectangle ){};
    
    void expand( const QPoint& point );
};

#endif /*RECT_H_*/
