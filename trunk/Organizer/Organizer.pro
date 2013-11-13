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
    Views/transactionView.cpp

HEADERS  += \
    OrganizerView.h \
    ../Common/drivers/driverSqlite.h \
    OrganizerConst.h \
    Dialog.h \
    Views/accountView.h \
    Views/transactionView.h

FORMS    += \
    OrganizerView.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ../Common/metascheme.xml
