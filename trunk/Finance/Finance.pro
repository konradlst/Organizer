#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T18:47:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Finance
TEMPLATE = app
INCLUDEPATH += "./View"

SOURCES += main.cpp\
    cgFinanceView.cpp \
    View/cgAccountList.cpp \
    View/cgTransactionList.cpp \
    View/cgTransactionView.cpp

HEADERS  += \
    cgFinanceView.h \
    View/cgAccountList.h \
    View/cgTransactionList.h \
    View/cgTransactionView.h

FORMS    += cgFinanceView.ui \
    View/cgTransactionView.ui
