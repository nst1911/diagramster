#-------------------------------------------------
#
# Project created by QtCreator 2021-02-18T08:56:35
#
#-------------------------------------------------

QT       += core gui xml testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diagramster
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    basicobjectmetafactory.cpp \
    basicobjectserializer.cpp \
    diagram.cpp \
        main.cpp \
    gui/mainwindow.cpp \
    figure.cpp \
    test/basicobjectserializertest.cpp \
    test/diagramtest.cpp \
    test/figures/connectionlinetest.cpp \
    test/figuretest.cpp \
    figures/block.cpp \
    test/figures/blocktest.cpp \
    figures/connectionline.cpp \
    basicobject.cpp \
    test/basicobjecttest.cpp

HEADERS += \
    basicobjectmetafactory.h \
    basicobjectserializer.h \
    diagram.h \
    gui/mainwindow.h \
    test/basicobjectserializertest.h \
    test/diagramtest.h \
    test/figures/connectionlinetest.h \
    test/tests.h \
    figure.h \
    test/figuretest.h \
    figures/block.h \
    test/figures/blocktest.h \
    figures/connectionline.h \
    basicobject.h \
    test/basicobjecttest.h

FORMS += \
    gui/mainwindow.ui

DISTFILES += \
    diagramster.qmodel \
    diagramstergui.qmodel
