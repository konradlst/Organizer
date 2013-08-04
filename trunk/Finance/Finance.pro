#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T20:38:22
#
#-------------------------------------------------

include(./local_deploy.pri)

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Finance
TEMPLATE = app
INCLUDEPATH += "../Common/dbGenerator"
INCLUDEPATH += "./View"

SOURCES += main.cpp\
        cgFinance.cpp \
        ../Common/dbGenerator/dbGenerator.cpp \
        View/cgFinanceView.cpp \
    View/cgAccountList.cpp

HEADERS  += \
        cgFinance.h \
        ../Common/dbGenerator/dbGenerator.h \
        View/cgFinanceView.h \
    View/cgAccountList.h

OTHER_FILES += \
    metascheme.xml
