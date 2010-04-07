#ifndef TSTPLOTTER_H
#define TSTPLOTTER_H

//#define PLOTTER_IMPORT

#include <scalewidget.h>
#include <rtplotter.h>
#include <canvas.h>
#include <curve.h>
#include <linearscalex.h>
#include <linearscaley.h>
#include <curvedata.h>


#include <QMainWindow>
#include <QTimer>

class TSTPlotter : public QMainWindow
{
    Q_OBJECT

public:
    TSTPlotter(QWidget *parent = 0);
    ~TSTPlotter();
    
    void start();

public slots:
	void newData();
    
private:
    Canvas  *cnv;
    RTPlotter	*plt;
	
    CurveData	*data;
		    
    LinearScaleX *scalex;
    LinearScaleY *scaley;
    
    Curve *crv;
    
    QTimer timer;
};

#endif // TSTPLOTTER_H
