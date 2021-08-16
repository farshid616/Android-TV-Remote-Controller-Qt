QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase qmltestcase

TEMPLATE = app

INCDIR = ../tv-remote-controller
INCLUDEPATH += $$INCDIR
HEADERS += 
SOURCES += 
SOURCES +=  tst_guitest.cpp

DISTFILES += \
    tst_testcase.qml


