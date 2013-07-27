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


SOURCES += main.cpp\
        cgFinance.cpp \
    dbGenerator.cpp

HEADERS  += cgFinance.h \
    dbGenerator.h

OTHER_FILES += \
    metascheme.xml
