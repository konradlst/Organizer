#include <QApplication>
#include <QTextCodec>
#include <QIcon>
#include "contactListController.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/app_pic"));
    a.setApplicationName("Сoncierge: Contact List");
    a.setApplicationVersion("0.2");
    a.setOrganizationDomain("a.batyaev@gmail.com");
    a.setOrganizationName("Anton Batyaev");

    ContactListController c;

    return a.exec();
}
