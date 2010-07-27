# -------------------------------------------------
# Project created by QtCreator 2010-07-27T12:08:58
# -------------------------------------------------
QT -= gui
TARGET = test
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
unix:INCLUDEPATH += /usr/include/glib-2.0 \
    /usr/lib/glib-2.0/include \
    /usr/include/libpurple
unix:LIBS += -lglib-2.0 \
    -lpurple
SOURCES += main.cpp \
    ../qpurpletimer.cpp \
    ../qpurpleionotifier.cpp \
    ../qpurple.cpp
HEADERS += ../qpurpletimer.h \
    ../qpurpleionotifier.h \
    ../qpurple.h
