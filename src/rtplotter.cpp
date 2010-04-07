
#include "rtplotter.h"
#include "linearscalex.h"  

RTPlotter::RTPlotter( Canvas *cnv, QWidget *parent, Qt::WindowFlags f ):Plotter( cnv, parent, f )
{
    XScale = new LinearScaleX();
};

RTPlotter::~RTPlotter()
{
    delete XScale;
};

void RTPlotter::buildFrame()
{
    Plotter::buildFrame();
};
   
void RTPlotter::drawNewData()
{
    double right_value=0;
    ItemList::iterator i = dynamicItems.begin();
    while (i != dynamicItems.end() )
    {
        right_value = qMax( right_value, (*i)->dataRect().right() );
        i++;
    };

    //Upadate reference point for X-scales since plot always must contain fresh data.
    //XScale->setRefPoint( , , 0);
    //fmod(right_value,XDiapason);
    
    Plotter::drawNewData();
};

void RTPlotter::setDiapason(double diapason)
{
    XDiapason = diapason;
};

double RTPlotter::diapason() const
{
    return XDiapason;
};
