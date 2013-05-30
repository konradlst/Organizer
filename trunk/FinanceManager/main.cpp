#include <QtGui/QApplication>
#include "financeManagerView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FinanceManagerView w;
    w.show();
    
    return a.exec();
}
