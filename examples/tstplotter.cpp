#include "tstplotter.h"

#include <grid.h>

#include <math.h>
#include <cstdlib>

TSTPlotter::TSTPlotter(QWidget *parent)
    : QMainWindow(parent)
{
  cnv = new Canvas();
  plt = new RTPlotter(cnv,this);
  data = new CurveData(200);
  plt->setDiapason(180);
  scalex = dynamic_cast<LinearScaleX*>(plt->xScale());
  scaley = new LinearScaleY();

  scaley->setFlags(LinearScale::ManualDiapason);
  scalex->setFlags(LinearScale::ManualDiapason);
  scaley->setManualDiapason(-12,12);
  scalex->setManualDiapason(0,400);
  
  crv = new Curve( "Test curve", "l/s", scalex, scaley, data );
  
  plt->attachDynamicItem(crv);

  Grid *grid = new Grid();
  plt->attachStaticItem(grid);

  setCentralWidget(plt);
  timer.connect( &timer, SIGNAL(timeout()), plt, SLOT(drawNewData()) );
  timer.connect( &timer, SIGNAL(timeout()), this, SLOT(newData())  );
  
};

TSTPlotter::~TSTPlotter()
{
  //delete scalex;
  //delete scalex;
  //delete crv;
  delete plt;
  delete cnv;
};

void TSTPlotter::newData()
{
	static int i;
	
	data->pushBack( QPointF(i*2,10*sin((double)i/5)*rand()/RAND_MAX) );
	i++;
	
	if( i > 200 )
	   i =0;
	  //qWarning("timeout");
};

void TSTPlotter::start()
{
	timer.start(50);
};
