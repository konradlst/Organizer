#ifndef CONVERTERVIEW_H
#define CONVERTERVIEW_H

#include <QWidget>
#include "converterController.h"

class QPushButton;
class QGridLayout;
class QLabel;
class QLineEdit;

class ConverterView : public QWidget
{
    Q_OBJECT
public:
    explicit ConverterView(ConverterController *controller, QWidget *parent = 0);

signals:
    void convert();
    void inputFileChanged(const QString &path);
    void outputFileChanged(const QString &path);

private:
    void createInterface();
    void createGrid();

private slots:
    void chooseInputFile();
    void chooseOutputFile();

private:
    ConverterController *m_controller;
    QGridLayout *m_lay;
    QPushButton *m_convert;
    QPushButton *m_chooseInputFile;
    QPushButton *m_chooseOutputFile;
    QLineEdit *m_inputFile;
    QLineEdit *m_outputFile;
    QLabel *m_lbInputFile;
    QLabel *m_lbOutputFile;
};

#endif // CONVERTERVIEW_H
