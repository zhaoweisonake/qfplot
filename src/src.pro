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
HEADERS +=  ../include/canvas.h \
    ../include/curve.h \
    ../include/curvedata.h \
    ../include/grid.h \
    ../include/linearscalex.h \
    ../include/linearscaley.h \
    ../include/plotitem.h \
    ../include/plotter.h \
    ../include/rect.h \
    ../include/rectf.h \
    ../include/ring.h \
    ../include/scale.h \
    ../include/scalewidget.h \

SOURCES += canvas.cpp \
    curve.cpp \
    curvedata.cpp \
    grid.cpp \
    linearscalex.cpp \
    linearscaley.cpp \
    plotitem.cpp \
    plotter.cpp \
    rect.cpp \
    rectf.cpp \
    ring.cpp \
    scale.cpp\
    scalewidget.cpp 