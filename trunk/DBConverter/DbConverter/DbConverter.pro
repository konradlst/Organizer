#-------------------------------------------------
#
# Project created by QtCreator 2013-10-18T20:28:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DbConverter
TEMPLATE = app

SOURCES += main.cpp \
        cgDbConverterView.cpp \
        ./Readers/cgCsvReader.cpp \
        ./Readers/cgSqliteReader.cpp

HEADERS  += \
        cgDbConverterView.h \
        ./Readers/cgReader.h \
        ./Readers/cgCsvReader.h \
        ./Readers/cgSqliteReader.h

FORMS    += cgDbConverterView.ui
