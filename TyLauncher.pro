#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T15:42:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = TyLauncher
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    appbutton.cpp \
    aboutdialog.cpp \
    appbuttondialog.cpp \
    dynamicdata.cpp \
    utils/uiutils.cpp \
    utils/apputils.cpp \
    tabwidget.cpp \
    model/appinfo.cpp

HEADERS  += mainwindow.h \
    appbutton.h \
    aboutdialog.h \
    StaticSetting.h \
    appbuttondialog.h \
    dynamicdata.h \
    TyLog_Qt.h \
    utils/uiutils.h \
    utils/apputils.h \
    tabwidget.h \
    datasettings.h \
    model/appinfo.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    appbuttondialog.ui

include(qxtglobalshortcut/qxtglobalshortcut.pri)

RESOURCES += \
    res.qrc

include(StaticSetting.h)
win32:RC_FILE += \
    TyLauncher.rc

TRANSLATIONS += language/zh_CN.ts

macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
    QMAKE_MAC_SDK = macosx # work around QTBUG-41238
    # Copy the custom Info.plist to the app bundle
    QMAKE_INFO_PLIST = ./shared/Info.plist

    # Only Intel binaries are accepted so force this
    CONFIG += x86
    LIBS += -framework Carbon -framework Cocoa
    QT += macextras

    # Icon is mandatory for submission
    ICON = res/icon.icns
}

DISTFILES += \
    language/zh_CN.qm