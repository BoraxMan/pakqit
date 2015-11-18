#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T22:18:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x
TARGET = PakEdit
TEMPLATE = app
CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp \
    pakmodel.cpp \
    treeitem.cpp \
    directoryentry.cpp \
    pak.cpp \
    dirmodel.cpp \
    func.cpp \
    exceptionhandler.cpp \
    paktreeview.cpp \
    pakexception.cpp \
    manual.cpp \
    qfunc.cpp

HEADERS  += mainwindow.h \
    pakmodel.h \
    treeitem.h \
    directoryentry.h \
    pak.h \
    dirmodel.h \
    func.h \
    exceptionhandler.h \
    paktreeview.h \
    pakexception.h \
    manual.h \
    qfunc.h

FORMS    += mainwindow.ui \
    about.ui \
    manual.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    README

#CONFIG = release
