#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

#include <QDialog>

namespace Ui {
class AboutView;
}

class AboutView : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutView(QWidget *parent = 0);
    ~AboutView();
    
private:
    Ui::AboutView *ui;
};

#endif // ABOUTVIEW_H
