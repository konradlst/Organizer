#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T20:06:01
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ContactList
TEMPLATE = app
INCLUDEPATH += "./include/"

SOURCES += main.cpp\
    contactListView.cpp \
    contactData.cpp \
    driverXml.cpp \
    contactListController.cpp \
    contactListModel.cpp \
    settingsView.cpp \
    myLog.cpp

HEADERS  += \
    ./include/contactListView.h \
    ./include/contactData.h \
    ./include/driverXml.h \
    ./include/contactListController.h \
    ./include/contactListModel.h \
    ./include/settingsView.h \
    ./include/myLog.h

FORMS    += contactListView.ui \
    settingsView.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += ContactList.ru_RU.ts
