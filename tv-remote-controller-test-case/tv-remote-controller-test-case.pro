QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCDIR = ../tv-remote-controller
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/settingshandler.h
SOURCES += $$INCDIR/settingshandler.cpp

SOURCES +=  tst_testcase.cpp
