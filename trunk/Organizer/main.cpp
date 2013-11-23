#include <QApplication>
#include <QTextCodec>
#include "OrganizerView.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/app_pic"));
    a.setApplicationName("Organizer");
    a.setApplicationVersion("0.3");
    a.setOrganizationDomain("a.batyaev@gmail.com");
    a.setOrganizationName("Anton Batyaev");

    OrganizerView w;
    w.show();
    
    return a.exec();
}
