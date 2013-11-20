#-------------------------------------------------
#
# Project created by QtCreator 2013-08-17T18:45:19
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Organizer
TEMPLATE = app
INCLUDEPATH += "../Common/"

SOURCES += main.cpp \
    OrganizerView.cpp \
    ../Common/drivers/driverSqlite.cpp \
    Dialog.cpp \
    Views/accountView.cpp \
    Views/transactionView.cpp \
    Views/timeView.cpp \
    Views/dealView.cpp \
    Views/dateView.cpp \
    Views/eventView.cpp \
    Views/yearCalendar.cpp

HEADERS  += \
    OrganizerView.h \
    ../Common/drivers/driverSqlite.h \
    OrganizerConst.h \
    Dialog.h \
    Views/accountView.h \
    Views/transactionView.h \
    Views/timeView.h \
    Views/dealView.h \
    Views/dateView.h \
    Views/eventView.h \
    Views/yearCalendar.h

FORMS    += \
    OrganizerView.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ../Common/metascheme.xml
