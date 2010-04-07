TEMPLATE += fakelib
PLOTTER_LIBNAME = $$qtLibraryTarget(Plotter)
TEMPLATE -= fakelib
PLOTTER_LIBDIR = $$PWD/lib
unix:plotter-uselib:!plotter-buildlib:QMAKE_RPATHDIR += $$PLOTTER_LIBDIR
PLOTTER_INCLUDEDIR = $$PWD/include

win32:plotter-buildlib:DEFINES += PLOTTER_EXPORT
win32:plotter-uselib:DEFINES += PLOTTER_IMPORT


