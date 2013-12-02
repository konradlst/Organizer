#-------------------------------------------------
#
# Project created by QtCreator 2013-08-17T18:45:19
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Organizer
TEMPLATE = app
INCLUDEPATH += "../Common/"
INCLUDEPATH += "../Common/dbGenerator"
INCLUDEPATH += "./modules"
INCLUDEPATH += "./modules/accounts"
INCLUDEPATH += "./modules/transactions"
INCLUDEPATH += "./modules/deals"
INCLUDEPATH += "./modules/times"
INCLUDEPATH += "./modules/calendars"
INCLUDEPATH += "./translation"


SOURCES += main.cpp \
    OrganizerView.cpp \
    modules/accounts/accountView.cpp \
    modules/accounts/accountDialog.cpp \
    modules/transactions/transactionView.cpp \
    modules/transactions/transactionDialog.cpp \
    modules/deals/dealView.cpp \
    modules/deals/eventView.cpp \
    modules/deals/dealDialog.cpp \
    modules/times/timeView.cpp \
    modules/times/timeDialog.cpp \
    modules/calendars/yearCalendar.cpp \
    modules/calendars/dateView.cpp \
    modules/dialog.cpp \
    ../Common/dbGenerator/dbGenerator.cpp \
    ../Common/drivers/driverSqlite.cpp \
    ../Common/cgMetaschemeConst.cpp \
    ../Common/logger.cpp

HEADERS  += \
    OrganizerView.h \
    OrganizerConst.h \
    modules/accounts/accountView.h \
    modules/accounts/accountDialog.h \
    modules/transactions/transactionView.h \
    modules/transactions/transactionDialog.h \
    modules/deals/dealView.h \
    modules/deals/eventView.h \
    modules/deals/dealDialog.h \
    modules/times/timeView.h \
    modules/times/timeDialog.h \
    modules/calendars/yearCalendar.h \
    modules/calendars/dateView.h \
    modules/dialog.h \
    modules/dialogConst.h \
    ../Common/dbGenerator/dbGenerator.h \
    ../Common/drivers/driverSqlite.h \
    ../Common/logger.h \
    ../Common/cgMetaschemeConst.cpp

FORMS    += \
    OrganizerView.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ./translation/Organizer.ru_RU.ts \
    ./translation/Organizer.en_US.ts

OTHER_FILES += \
    ../Common/metascheme_0.3.xml
