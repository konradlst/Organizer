#include "cgFinance.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cgFinance w;
    w.show();
    
    return a.exec();
}
