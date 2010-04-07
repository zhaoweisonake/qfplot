TEMPLATE=lib
CONFIG += qt plotter-buildlib
infile(config.pri, PLOTTER_SHARED_LIBRARY, yes): CONFIG += dll
mac:CONFIG += absolute_library_soname

include(../plotter.pri)
TARGET = $$PLOTTER_LIBNAME
DESTDIR = $$PLOTTER_LIBDIR
INCLUDEPATH += $$PLOTTER_INCLUDEDIR
DEPENDPATH += $$PWD

#Build folders
system(mkdir .obj)
system(mkdir .moc)

OBJECTS_DIR = .obj    
MOC_DIR = .moc

# Input files
HEADERS += ../include/axis.h \
    ../include/canvas.h \
    ../include/curve.h \
    ../include/curvedata.h \
    ../include/grid.h \
    ../include/linearscale.h \
    ../include/linearscalex.h \
    ../include/linearscaley.h \
    ../include/log10scale.h \
    ../include/log10scalex.h \
    ../include/log10scaley.h \
    ../include/plotitem.h \
    ../include/plotter.h \
    ../include/rtplotter.h \
    ../include/rect.h \
    ../include/rectf.h \
    ../include/ring.h \
    ../include/scale.h \
    ../include/scalewidget.h \
    ../include/rtlinearscalex.h

SOURCES += axis.cpp \
    canvas.cpp \
    curve.cpp \
    curvedata.cpp \
    grid.cpp \
    iscale.cpp \
    linearscale.cpp \
    linearscalex.cpp \
    linearscaley.cpp \
    log10scale.cpp \
    log10scalex.cpp \
    log10scaley.cpp \
    plotitem.cpp \
    plotter.cpp \
    rtplotter.cpp \ 
    rect.cpp \
    rectf.cpp \
    ring.cpp \
    scalewidget.cpp \
    rtlinearscalex.cpp
