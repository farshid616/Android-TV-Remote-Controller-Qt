QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase qmltestcase

TEMPLATE = app

INCDIR = ../tv-remote-controller
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/settingshandler.h \
           $$INCDIR/messagehandler.h \
           devicemodeltestcase.h \
           messagehandlertestcase.h \
           settingshandlertestcase.h \
           $$INCDIR/datamodel.h \
           $$INCDIR/devicemodel.h
SOURCES += $$INCDIR/settingshandler.cpp \
           $$INCDIR/messagehandler.cpp \
           devicemodeltestcase.cpp \
           messagehandlertestcase.cpp \
           settingshandlertestcase.cpp \
           $$INCDIR/devicemodel.cpp

SOURCES +=  tst_testcase.cpp

DISTFILES +=
