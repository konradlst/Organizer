#include "cgFinanceView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cgFinanceView w;
    w.show();
    
    return a.exec();
}
