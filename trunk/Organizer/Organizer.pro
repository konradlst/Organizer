#-------------------------------------------------
#
# Project created by QtCreator 2013-08-17T18:45:19
#
#-------------------------------------------------

include(../Common/local_deploy.pri)

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
INCLUDEPATH += "./modules/contacts"
INCLUDEPATH += "./translation"

SOURCES += main.cpp \
    OrganizerView.cpp \
    modules/abstractModule.cpp \
    modules/accounts/accountView.cpp \
    modules/accounts/accountDialog.cpp \
    modules/transactions/transactionView.cpp \
    modules/transactions/transactionDialog.cpp \
    modules/deals/dealView.cpp \
    modules/deals/eventView.cpp \
    modules/deals/dealDialog.cpp \
    modules/times/timeView.cpp \
    modules/times/timeDialog.cpp \
    modules/calendars/dateView.cpp \
    modules/calendars/yearCalendar.cpp \
    modules/contacts/contactDialog.cpp \
    modules/contacts/channelDialog.cpp \
    modules/contacts/addressDialog.cpp \
    modules/contacts/companyDialog.cpp \
    modules/contacts/channelView.cpp \
    modules/contacts/companyView.cpp \
    modules/contacts/addressView.cpp \
    modules/contacts/contactView.cpp \
    modules/dialog.cpp \
    ../Common/dbGenerator/dbGenerator.cpp \
    ../Common/drivers/driverSqlite.cpp \
    ../Common/cgMetaschemeConst.cpp \
    ../Common/logger.cpp

HEADERS  += \
    OrganizerView.h \
    OrganizerConst.h \
    modules/abstractModule.h \
    modules/accounts/accountView.h \
    modules/accounts/accountDialog.h \
    modules/accounts/accountData.h \
    modules/transactions/transactionView.h \
    modules/transactions/transactionDialog.h \
    modules/deals/dealView.h \
    modules/deals/eventView.h \
    modules/deals/dealDialog.h \
    modules/times/timeView.h \
    modules/times/timeDialog.h \
    modules/calendars/dateView.h \
    modules/calendars/yearCalendar.h \
    modules/contacts/contactsConst.h \
    modules/contacts/contactDialog.h \
    modules/contacts/channelDialog.h \
    modules/contacts/addressDialog.h \
    modules/contacts/companyDialog.h \
    modules/contacts/channelView.h \
    modules/contacts/companyView.h \
    modules/contacts/addressView.h \
    modules/contacts/contactView.h \
    modules/contacts/contactData.h \
    modules/contacts/companyData.h \
    modules/dialogConst.h \
    modules/dialog.h \
    ../Common/dbGenerator/dbGenerator.h \
    ../Common/drivers/driverSqlite.h \
    ../Common/cgMetaschemeConst.cpp \
    ../Common/logger.h \
    modules/transactions/transactionData.h \
    modules/contacts/addressData.h \
    modules/contacts/channelData.h \
    modules/times/timeData.h

FORMS    += \
    OrganizerView.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    ./translation/Organizer.ru_RU.ts \
    ./translation/Organizer.en_US.ts

OTHER_FILES += \
    ../Common/metascheme_0.3.xml
