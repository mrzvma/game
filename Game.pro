#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T17:00:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
    basesprite.cpp \
        widget.cpp \
    scenebuffer.cpp \
    controlsprite.cpp \
    spriteenemy.cpp \
    spriterocket.cpp \
    generatorsprates.cpp \
    resurseimages.cpp \
    panelelement.cpp \
    panelelemprogressbar.cpp

HEADERS  += widget.h \
    scenebuffer.h \
    controlsprite.h \
    basesprite.h \
    spriteenemy.h \
    spriterocket.h \
    generatorsprates.h \
    resurseimages.h \
    panelelement.h \
    panelelemprogressbar.h
QMAKE_LFLAGS +=  -static -static-libgcc -std=c++11

RESOURCES += \
    images.qrc

CONFIG += c++11

DISTFILES +=
