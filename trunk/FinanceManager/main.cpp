#include <QtGui/QApplication>
#include "financeManagerController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FinanceManagerController c;

    return a.exec();
}
