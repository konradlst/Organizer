#ifndef CGDBCONVERTERVIEW_H
#define CGDBCONVERTERVIEW_H

#include <QMainWindow>

namespace Ui {
class cgDbConverterView;
}

class cgDbConverterView : public QMainWindow
{
    Q_OBJECT

public:
    explicit cgDbConverterView(QWidget *parent = 0);
    ~cgDbConverterView();

private slots:
    void on_pbChooseSourceFile_clicked();
    void on_pbChooseNewFile_clicked();
    void on_Convert_clicked();

private:
    Ui::cgDbConverterView *ui;
};

#endif // CGDBCONVERTERVIEW_H
