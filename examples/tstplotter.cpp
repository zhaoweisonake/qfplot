#include "tstplotter.h"

#include <grid.h>

#include <math.h>
#include <cstdlib>

TSTPlotter::TSTPlotter(QWidget *parent)
    : QMainWindow(parent)
{
  plt = new Plotter(CanvasPtr(),this);
  data = new CurveData(200);

  plt->xScale()->setFlags(Scale::ManualDiapason);
  plt->yScale()->setFlags(Scale::ManualDiapason);
  plt->yScale()->setManualDiapason(-12,12);
  plt->xScale()->setManualDiapason(0,80);
  
  crv = new Curve( "Test curve", "l/s", plt->xScale(), plt->yScale(), data );
  
  plt->attachDynamicItem(crv);

  Grid *grid = new Grid();
  plt->attachStaticItem(grid);

  setCentralWidget(plt);
  newData(); 
};

TSTPlotter::~TSTPlotter()
{
  //delete grid;
  delete crv;
  delete data;
};

void TSTPlotter::newData()
{
	int i;
	for(i=0;i<50;i++)
	 data->pushBack( QPointF(i*2,10*sin((double)i/5)*rand()/RAND_MAX) );
};

