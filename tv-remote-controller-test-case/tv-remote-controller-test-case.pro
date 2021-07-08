QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCDIR = ../tv-remote-controller
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/settingshandler.h \
           $$INCDIR/messagehandler.h \
           messagehandlertestcase.h \
           settingshandlertestcase.h \
           $$INCDIR/datamodel.h
SOURCES += $$INCDIR/settingshandler.cpp \
           $$INCDIR/messagehandler.cpp \
           messagehandlertestcase.cpp \
           settingshandlertestcase.cpp

SOURCES +=  tst_testcase.cpp
