#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T14:30:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarleneAdmin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    uicardbroker.cpp

HEADERS  += mainwindow.h \
    uicardbroker.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/../MarleneLib
debug {
LIBS += -L$$PWD/../build-MarleneLib-Debug/debug -lMarleneLib
}
release {
LIBS += -L$$PWD/../build-MarleneLib-Release/release -lMarleneLib
}

win32 {
INCLUDEPATH += C:\BasicCardPro\Api\H
LIBS += -LC:\BasicCardPro\Api\Lib\MS_new -lzccri -lzcbci
}
