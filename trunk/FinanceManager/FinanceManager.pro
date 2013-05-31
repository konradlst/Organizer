#-------------------------------------------------
#
# Project created by QtCreator 2013-05-30T14:59:24
#
#-------------------------------------------------

QT       += core gui

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
    include/financeManagerModel.h

FORMS    += financeManagerView.ui
