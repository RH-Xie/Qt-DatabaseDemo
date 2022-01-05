#-------------------------------------------------
#
# Project created by QtCreator 2021-12-22T18:03:06
#
#-------------------------------------------------

QT       += core gui
QT       += sql
RC_ICONS += icon.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = databaseDemo2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    loginform.cpp \
    mainwindow.cpp \
    sql.cpp \
    usergroup.cpp \
    modifyform.cpp \
    addform.cpp \
    resetpw.cpp

HEADERS += \
        mainwindow.h \
    loginform.h \
    sql.h \
    usergroup.h \
    modifyform.h \
    addform.h \
    resetpw.h

DISTFILES +=

RESOURCES += \
    texture.qrc
