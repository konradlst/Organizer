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
INCLUDEPATH += "./Views/"
INCLUDEPATH += "./Dialogs/"


SOURCES += main.cpp \
    OrganizerView.cpp \
    ../Common/drivers/driverSqlite.cpp \
    Views/accountView.cpp \
    Views/transactionView.cpp \
    Views/timeView.cpp \
    Views/dealView.cpp \
    Views/dateView.cpp \
    Views/eventView.cpp \
    Views/yearCalendar.cpp \
    Dialogs/dialog.cpp \
    Dialogs/timeDialog.cpp \
    Dialogs/dealDialog.cpp \
    Dialogs/accountDialog.cpp \
    Dialogs/transactionDialog.cpp

HEADERS  += \
    OrganizerView.h \
    ../Common/drivers/driverSqlite.h \
    OrganizerConst.h \
    Views/accountView.h \
    Views/transactionView.h \
    Views/timeView.h \
    Views/dealView.h \
    Views/dateView.h \
    Views/eventView.h \
    Views/yearCalendar.h \
    Dialogs/dialog.h \
    Dialogs/dialogConst.h \
    Dialogs/timeDialog.h \
    Dialogs/dealDialog.h \
    Dialogs/accountDialog.h \
    Dialogs/transactionDialog.h

FORMS    += \
    OrganizerView.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ../Common/metascheme.xml
