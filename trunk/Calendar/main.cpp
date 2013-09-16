#include "cgCalendarView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CgCalendarView w;
    w.show();

    return a.exec();
}
