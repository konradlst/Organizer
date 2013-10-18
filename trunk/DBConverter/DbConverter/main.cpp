#include "cgDbConverterView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cgDbConverterView w;
    w.show();

    return a.exec();
}
