#-------------------------------------------------
#
# Project created by QtCreator 2012-02-19T20:39:08
#
#-------------------------------------------------

QT       += core
QT       += gui

TARGET = Estimator
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

QMAKE_CXXFLAGS += -g -std=c++0x

INCLUDEPATH  += /usr/include
INCLUDEPATH  += /usr/include/qt4/Qt
INCLUDEPATH  += /usr/include/qt4/QtGui
INCLUDEPATH  += /home/vmplanet/Documents/examples/cplusplus/wifislam_test/jsoncpp-src-0.5.0/include
INCLUDEPATH  += .

HEADERS += \
    JSONHandles.hpp \
    Location.hpp \
    VectorUtils.hpp \
    ComplexUtils.hpp \
    INCHeaders.hpp

LIBS  += -ljson_linux-gcc-4.6.1_libmt
LIBS  += -lqwt-qt4

SOURCES += main.cpp
