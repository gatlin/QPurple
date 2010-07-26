# -------------------------------------------------
# Project created by QtCreator 2010-07-16T23:59:24
# -------------------------------------------------
QT += network \
    xml
QT -= gui
TARGET = qpurple
TEMPLATE = lib
DEFINES += QPURPLE_LIBRARY
unix:INCLUDEPATH += /usr/include/glib-2.0 \
    /usr/lib/glib-2.0/include \
    /usr/include/libpurple
unx:LIBS += -lglib-2.0 \
    -lpurple
SOURCES += qpurple.cpp \
    qpurpletimer.cpp \
    qpurpleionotifier.cpp
HEADERS += qpurple.h \
    qpurpletimer.h \
    qpurpleionotifier.h
