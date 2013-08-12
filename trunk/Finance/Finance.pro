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
INCLUDEPATH += "../Common/"
INCLUDEPATH += "../Common/dbGenerator"
INCLUDEPATH += "../Common/delegates"
INCLUDEPATH += "./View"

SOURCES += main.cpp\
    cgFinance.cpp \
    ../Common/dbGenerator/dbGenerator.cpp \
    View/cgAccountList.cpp \
    View/cgTransactionList.cpp \
    ../Common/delegates/cgComboBoxDelegate.cpp \
    ../Common/delegates/cgLineEditDelegate.cpp \
    ../Common/delegates/cgDateDelegate.cpp \
    ../Common/delegates/cgTimeDelegate.cpp \
    ../Common/delegates/cgDateTimeDelegate.cpp \
    ../Common/delegates/cgDelegateManager.cpp \
    ../Common/delegates/cgCheckBoxDelegate.cpp \
    ../Common/delegates/cgSpinBoxDelegate.cpp

HEADERS  += \
    cgFinance.h \
    ../Common/dbGenerator/dbGenerator.h \
    View/cgAccountList.h \
    View/cgTransactionList.h \
    ../Common/cgErrorMessage.h \
    ../Common/delegates/cgComboBoxDelegate.h \
    ../Common/delegates/cgLineEditDelegate.h \
    ../Common/delegates/cgDateDelegate.h \
    ../Common/delegates/cgTimeDelegate.h \
    ../Common/delegates/cgDateTimeDelegate.h \
    ../Common/delegates/cgDelegateManager.h \
    ../Common/delegates/cgCheckBoxDelegate.h \
    ../Common/delegates/cgSpinBoxDelegate.h

OTHER_FILES += \
    metascheme.xml \
    ../Common/metascheme.xml
