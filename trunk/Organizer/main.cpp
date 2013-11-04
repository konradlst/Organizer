#include <QApplication>
#include <QTextCodec>
#include "conciergeView.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/app_pic"));
    a.setApplicationName("Organizer");
    a.setApplicationVersion("0.1");
    a.setOrganizationDomain("a.batyaev@gmail.com");
    a.setOrganizationName("Anton Batyaev");

    ConciergeView w;
    w.show();
    
    return a.exec();
}
