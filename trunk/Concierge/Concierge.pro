#-------------------------------------------------
#
# Project created by QtCreator 2013-08-17T18:45:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Сoncierge
TEMPLATE = app


SOURCES += main.cpp\
        conciergeView.cpp \
    ../Common/drivers/driverSqlite.cpp

HEADERS  += conciergeView.h \
    ../Common/drivers/driverSqlite.h

FORMS    += conciergeView.ui
