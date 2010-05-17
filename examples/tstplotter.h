#ifndef TSTPLOTTER_H
#define TSTPLOTTER_H

//#define PLOTTER_IMPORT

#include <scalewidget.h>
#include <plotter.h>
#include <canvas.h>
#include <curve.h>
#include <linearscalex.h>
#include <linearscaley.h>
#include <curvedata.h>


#include <QMainWindow>

class TSTPlotter : public QMainWindow
{
    Q_OBJECT

public:
    TSTPlotter(QWidget *parent = 0);
    ~TSTPlotter();
    
public slots:
	void newData();
    
private:
    Plotter	*plt;
	
    CurveData	*data;
		    
    LinearScaleX *scalex;
    LinearScaleY *scaley;
    
    Curve *crv;
};

#endif // TSTPLOTTER_H
