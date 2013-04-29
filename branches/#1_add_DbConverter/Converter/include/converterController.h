#ifndef CONVERTERCONTROLLER_H
#define CONVERTERCONTROLLER_H

#include <QWidget>

class ConverterModel;
class ConverterView;

class ConverterController : public QWidget
{
    Q_OBJECT
public:
    explicit ConverterController(QWidget *parent = 0);

private:
    ConverterModel *m_model;
    ConverterView *m_view;
};

#endif // CONVERTERCONTROLLER_H
