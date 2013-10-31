#ifndef CGDBCONVERTERVIEW_H
#define CGDBCONVERTERVIEW_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QComboBox;

class cgDbConverterView : public QWidget
{
    Q_OBJECT

public:
    explicit cgDbConverterView(QWidget *parent = 0);

private slots:
    void on_pbChooseSourceFile_clicked();
    void on_pbChooseNewFile_clicked();
    void on_Convert_clicked();

private:
    QPushButton *m_chooseSourceFile;
    QPushButton *m_chooseNewFile;
    QPushButton *m_convert;
    QLineEdit *m_sourceFile;
    QLineEdit *m_newFile;
    QComboBox *m_sourceFileFormat;
    QComboBox *m_newFileFormat;
};

#endif // CGDBCONVERTERVIEW_H
