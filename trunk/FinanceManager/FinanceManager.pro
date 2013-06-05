#-------------------------------------------------
#
# Project created by QtCreator 2013-05-30T14:59:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinanceManager
TEMPLATE = app
INCLUDEPATH += "./include/"

SOURCES += main.cpp\
        financeManagerView.cpp \
    financeManagerController.cpp \
    financeManagerModel.cpp

HEADERS  += \
    include/financeManagerView.h \
    include/financeManagerController.h \
    include/financeManagerModel.h \
    include/financeManagerData.h

FORMS    += financeManagerView.ui
