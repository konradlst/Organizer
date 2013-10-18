#include <QFileDialog>
#include "cgDbConverterView.h"
#include "ui_cgDbConverterView.h"
#include "Readers/cgReader.h"
#include "Readers/cgCsvReader.h"
#include "Readers/cgSqliteReader.h"

namespace
{
    const QString Separator = ";;";
    const QString TitleChooseSourceFile = QObject::trUtf8("DbConverter: Choose source database.");
    const QString TitleChooseNewFile = QObject::trUtf8("DbConverter: Choose source database.");
    const QStringList FileTypes = QObject::trUtf8("All Files (*.*);;CSV files (*.csv);;SQLite files (*.sqlite)").split(Separator);
}

cgDbConverterView::cgDbConverterView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::cgDbConverterView)
{
    ui->setupUi(this);
    ui->SourceFileFormat->addItems(FileTypes);
    ui->NewFileFormat->addItems(FileTypes);
}

cgDbConverterView::~cgDbConverterView()
{
    delete ui;
}

void cgDbConverterView::on_pbChooseSourceFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, TitleChooseSourceFile, QDir::currentPath(), FileTypes.join(Separator));
    ui->SourceFile->setText(path);
    ui->SourceFileFormat->setCurrentText(FileTypes.filter(QFileInfo(path).suffix()).first());
}

void cgDbConverterView::on_pbChooseNewFile_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, TitleChooseNewFile, QDir::currentPath(), FileTypes.join(Separator));
    ui->NewFile->setText(path);
    ui->NewFileFormat->setCurrentText(FileTypes.filter(QFileInfo(path).suffix()).first());
}

void cgDbConverterView::on_Convert_clicked()
{
    QString typeFrom = QFileInfo(ui->SourceFileFormat->currentText()).suffix();
    QString typeTo = QFileInfo(ui->SourceFileFormat->currentText()).suffix();
}
