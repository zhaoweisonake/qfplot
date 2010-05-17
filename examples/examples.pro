TEMPLATE = app

TARGET = TSTPlotter
CONFIG += console plotter-uselib

include(../plotter.pri)

#Build folders
system(mkdir .obj)
system(mkdir .moc)

OBJECTS_DIR = .obj    
MOC_DIR = .moc

#Input    
HEADERS += tstplotter.h
SOURCES += main.cpp \
    tstplotter.cpp

#Plotter library
INCLUDEPATH += $$PLOTTER_INCLUDEDIR
LIBS += -L$$PLOTTER_LIBDIR -lPlotter 
    

