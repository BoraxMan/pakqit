#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T22:18:45
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x
TARGET = pakqit
TEMPLATE = app

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG(release, debug|release):DEFINES += NDEBUG
CONFIG(release, debug|release):QMAKE_CXXFLAGS += -fexpensive-optimizations

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
    qfunc.h \
    config.h.in

FORMS    += mainwindow.ui \
    about.ui \
    manual.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    README pakqit.spec menu/pakqit.desktop doc/LICENSE \
    pakqit.rc

VERSION = 0.2.0

versionconfig.input = config.h.in
versionconfig.output = config.h
QMAKE_SUBSTITUTES += versionconfig


FILE = $$TARGET-$$VERSION
EXTENSION=".tar.gz"


spec.input = pakqit.spec.in
spec.output = $$PWD/pakqit.spec
QMAKE_SUBSTITUTES += spec

win32: RC_FILE += pakqit.rc
win32: RC_ICONS = Quake-icon.ico

DISTFILES += \
    checkitgui.spec graphics/checkitgui.png menu/checkitgui.desktop \
    doc/LICENSE

documentation.files = doc/README.md doc/LICENSE
applications.files = menu/pakqit.desktop
icons.files = icons/pakqit.png

target.path = $$PREFIX/usr/bin
documentation.path = $$PREFIX/usr/share/doc/$$TARGET
applications.path = $$PREFIX/usr/share/applications
icons.path = $$PREFIX/usr/share/icons/hicolor/64x64/apps

INSTALLS += target documentation applications icons

#CONFIG = release
