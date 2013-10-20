#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include "cgDbConverterView.h"
#include "Readers/cgCsvReader.h"
#include "Readers/cgSqliteReader.h"

namespace
{
    const int AllFiles = 0;
    const QString Separator = ";;";
    const QString lblFrom = QObject::trUtf8("From :");
    const QString lblTo = QObject::trUtf8("To :");
    const QString Title = QObject::trUtf8("Сoncierge: DbConverter");
    const QString TitleChooseSourceFile = QObject::trUtf8("DbConverter: Choose source database.");
    const QString TitleChooseNewFile = QObject::trUtf8("DbConverter: Choose source database.");
    const QStringList FileTypes = QObject::trUtf8("All Files (*.*);;CSV files (*.csv);;SQLite files (*.sqlite)").split(Separator);
}

cgDbConverterView::cgDbConverterView(QWidget *parent)
    : QWidget(parent),
      m_chooseSourceFile(new QPushButton("...")),
      m_chooseNewFile(new QPushButton("...")),
      m_convert(new QPushButton("Convert")),
      m_sourceFile(new QLineEdit()),
      m_newFile(new QLineEdit()),
      m_sourceFileFormat(new QComboBox()),
      m_newFileFormat(new QComboBox())
{
    m_chooseSourceFile->setFixedSize(25, 25);
    m_chooseNewFile->setFixedSize(25, 25);
    m_sourceFileFormat->addItems(FileTypes);
    m_newFileFormat->addItems(FileTypes);

    QLabel *lblSourceFile = new QLabel(lblFrom);
    QLabel *lblNewFile = new QLabel(lblTo);
    QGridLayout *mLayout = new QGridLayout();
    mLayout->addWidget(lblSourceFile, 0, 0);
    mLayout->addWidget(lblNewFile, 1, 0);
    mLayout->addWidget(m_sourceFile, 0, 1);
    mLayout->addWidget(m_newFile, 1, 1);
    mLayout->addWidget(m_chooseSourceFile, 0, 2);
    mLayout->addWidget(m_chooseNewFile, 1, 2);
    mLayout->addWidget(m_sourceFileFormat, 0, 3);
    mLayout->addWidget(m_newFileFormat, 1, 3);
    mLayout->addWidget(m_convert, 2, 3);
    setLayout(mLayout);
    setFixedSize(475, 165);
    setWindowTitle(Title);

    connect(m_chooseSourceFile, SIGNAL(clicked()), this, SLOT(on_pbChooseSourceFile_clicked()));
    connect(m_chooseNewFile, SIGNAL(clicked()), this, SLOT(on_pbChooseNewFile_clicked()));
    connect(m_convert, SIGNAL(clicked()), this, SLOT(on_Convert_clicked()));
}

void cgDbConverterView::on_pbChooseSourceFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, TitleChooseSourceFile, QDir::currentPath(), FileTypes.join(Separator));
    m_sourceFile->setText(path);

    foreach (const QString &type, FileTypes)
    {
        if (type.contains(QFileInfo(path).suffix()))
        {
            m_sourceFileFormat->setCurrentText(type);
            return;
        }
    }
    m_sourceFileFormat->setCurrentIndex(AllFiles);
}

void cgDbConverterView::on_pbChooseNewFile_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, TitleChooseNewFile,
                                                QDir::currentPath(), FileTypes.join(Separator));
    m_newFile->setText(path);

    foreach (const QString &type, FileTypes)
    {
        if (type.contains(QFileInfo(path).suffix()))
        {
            m_newFileFormat->setCurrentText(type);
            return;
        }
    }
    m_newFileFormat->setCurrentIndex(AllFiles);
}

void cgDbConverterView::on_Convert_clicked()
{
    QString PathFrom = m_sourceFile->text();
    QString PathTo = m_newFile->text();
}
