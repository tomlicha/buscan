# -------------------------------------------------
# Project created by QtCreator 2011-05-31T11:30:38
# -------------------------------------------------
QT +=           opengl

TARGET =        mpu9250-OpenGl

TEMPLATE =      app

SOURCES +=      src/main.cpp \
    can_bus_ihm.cpp
SOURCES +=      src/mainwindow.cpp
SOURCES +=      src/objectgl.cpp
SOURCES +=      src/qcgaugewidget.cpp
SOURCES +=
SOURCES +=

HEADERS +=      include/mainwindow.h \
    can_bus_ihm.h
HEADERS +=      include/objectgl.h
HEADERS +=      include/qcgaugewidget.h
HEADERS +=
HEADERS +=

INCLUDEPATH +=  src
INCLUDEPATH +=  include

LIBS        += -lpcan

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
DESTDIR = bin/

FORMS += \
    can_bus_ihm.ui

DISTFILES +=
