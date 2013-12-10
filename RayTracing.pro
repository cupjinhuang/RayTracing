#-------------------------------------------------
#
# Project created by QtCreator 2013-11-30T22:47:15
#
#-------------------------------------------------

QT       += core gui

TARGET = RayTracing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    camera.cpp \
    ball.cpp \
    point.cpp \
    matrix.cpp \
    ray.cpp \
    intensity.cpp \
    color.cpp \
    model.cpp \
    source.cpp \
    plane.cpp \
    box.cpp \
    polygon.cpp

HEADERS  += mainwindow.h \
    scene.h \
    camera.h \
    ball.h \
    point.h \
    matrix.h \
    ray.h \
    intensity.h \
    color.h \
    model.h \
    source.h \
    plane.h \
    box.h \
    polygon.h

QMAKE_CXXFLAGS += -O3 #-pg
#QMAKE_LFLAGS += -pg
