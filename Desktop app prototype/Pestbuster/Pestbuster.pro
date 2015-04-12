#-------------------------------------------------
#
# Project created by QtCreator 2015-04-11T15:41:36
#
#-------------------------------------------------

QT       += core gui sql webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pestbuster
TEMPLATE = app


SOURCES += main.cpp\
        maindlg.cpp \
    dataaccess.cpp \

HEADERS  += maindlg.h \
    dataaccess.h \

FORMS    += maindlg.ui

RESOURCES += \
    resources.qrc
