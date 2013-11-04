#-------------------------------------------------
#
# Project created by QtCreator 2013-08-17T18:45:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Organizer
TEMPLATE = app


SOURCES += main.cpp \
    ConciergeView.cpp \
    ../Common/drivers/driverSqlite.cpp

HEADERS  += \
    ConciergeView.h \
    ../Common/drivers/driverSqlite.h

FORMS    += \
    ConciergeView.ui

RESOURCES += \
    res.qrc
