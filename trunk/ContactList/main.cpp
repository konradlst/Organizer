#include "contactListController.h"
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QIcon>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/app_pic"));
    a.setApplicationName("Contact List");
    a.setApplicationVersion("0.1.1");
    a.setOrganizationDomain("a.batyaev@gmail.com");
    a.setOrganizationName("Batyaev Anton");

    QTranslator tr, qt_tr;
    tr.load(":/lang_ru_RU");
    qt_tr.load(":/qt_ru_RU");
    a.installTranslator(&tr);
    a.installTranslator(&qt_tr);

    ContactListController c;
    
    return a.exec();
}
