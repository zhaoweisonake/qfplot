#ifndef RECTF_H_
#define RECTF_H_

#include <QRectF>

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


class PLOTTER_EXPORT RectF : public QRectF
{
	public:
	inline RectF ()
	:QRectF (){};
	
    inline RectF ( const QPointF & topLeft, const QSizeF & size )
    : QRectF ( topLeft, size ){};
    
    inline RectF ( qreal x, qreal y, qreal width, qreal height )
    : QRectF (x, y, width, height ){};
    
    inline RectF ( const QRect & rectangle )
    : QRectF ( rectangle ){};
    
	void expand(const QPointF& point );
};

#endif /*RECTF_H_*/
