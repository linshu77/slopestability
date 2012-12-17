#-------------------------------------------------
#
# Project created by QtCreator 2012-12-17T12:36:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = slopestability
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    rowadd.cpp \
    rowdelete.cpp \
    algorithm.cpp \
    resultswindow.cpp

HEADERS  += \
    mainwindow.h \
    rowadd.h \
    rowdelete.h \
    algorithm.h \
    resultswindow.h

FORMS    += \
    rowadd.ui \
    rowdelete.ui
