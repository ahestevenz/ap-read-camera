#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T10:37:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = pgrey
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
           apOCVPointGrey.cpp

HEADERS += \
           apOCVPointGrey.hpp

INCLUDEPATH += 	/usr/local/include/opencv2/ \
                /usr/local/include/opencv/  \
                /usr/include/flycapture/  \


CFLAGS=-I/usr/include/libavcodec
CPPFLAGS=-I/usr/include/libavcodec

QMAKE_CXXFLAGS += -std=c++11

LIBS += `pkg-config --libs opencv`
LIBS += /usr/lib/libflycapture.so

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
} else {
    DESTDIR = build/release
}
