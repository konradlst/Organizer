#include <QApplication>
#include <QTextCodec>
#include "cgDBManager.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setApplicationName("Organizer: DBManager");
    a.setApplicationVersion("0.3");
    a.setOrganizationDomain("a.batyaev@gmail.com");
    a.setOrganizationName("Anton Batyaev");

    cgDBManager w;
    w.show();

    return a.exec();
}
