#include <QApplication>
#include <QTextCodec>
#include "cgCalendarView.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setApplicationName("Сoncierge: Calendar");
    a.setApplicationVersion("0.2");
    a.setOrganizationDomain("a.batyaev@gmail.com");
    a.setOrganizationName("Anton Batyaev");

    CgCalendarView w;
    w.show();

    return a.exec();
}
