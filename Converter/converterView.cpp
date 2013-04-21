#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include "converterView.h"

namespace {
#define chooseFileLabel "..."
#define inputFileLabel QObject::trUtf8("Input File: ")
#define outputFileLabel QObject::trUtf8("Output File: ")
#define convert QObject::trUtf8("Convert file")
#define defSizeButton QSize(22,22)
#define titleChooseInputFile QObject::trUtf8("Choose a input file")
#define titleChooseOutputFile QObject::trUtf8("Choose a output file")
}
ConverterView::ConverterView(ConverterController *controller, QWidget *parent) :
    QWidget(parent),
    m_controller(controller),
    m_lay(new QGridLayout),
    m_convert(new QPushButton(convert)),
    m_chooseInputFile(new QPushButton(chooseFileLabel)),
    m_chooseOutputFile(new QPushButton(chooseFileLabel)),
    m_inputFile(new QLineEdit),
    m_outputFile(new QLineEdit),
    m_lbInputFile(new QLabel(inputFileLabel)),
    m_lbOutputFile(new QLabel(outputFileLabel))
{
    createInterface();
    createGrid();
    connect(m_chooseInputFile,SIGNAL(clicked()),SLOT(chooseInputFile()));
    connect(m_chooseOutputFile,SIGNAL(clicked()),SLOT(chooseOutputFile()));
    connect(m_inputFile,SIGNAL(textChanged(QString)),SIGNAL(inputFileChanged(QString)));
    connect(m_outputFile,SIGNAL(textChanged(QString)),SIGNAL(outputFileChanged(QString)));
    connect(m_convert,SIGNAL(clicked()),SIGNAL(convert()));
}

void ConverterView::createInterface()
{
    m_chooseInputFile->setFixedSize(defSizeButton);
    m_chooseOutputFile->setFixedSize(defSizeButton);
}

void ConverterView::createGrid()
{
    m_lay->setSpacing(0);
    m_lay->addWidget(m_lbInputFile,0,0);
    m_lay->addWidget(m_inputFile,1,0);
    m_lay->addWidget(m_chooseInputFile,1,1);
    m_lay->addWidget(m_lbOutputFile,2,0);
    m_lay->addWidget(m_outputFile,3,0);
    m_lay->addWidget(m_chooseOutputFile,3,1);
    m_lay->addWidget(m_convert,4,0,1,2);
    setLayout(m_lay);
}

void ConverterView::chooseInputFile()
{
    QString inputFile;

    inputFile = QFileDialog::getOpenFileName(this,titleChooseInputFile);
    if(!inputFile.isNull()){
        m_inputFile->setText(inputFile);
    }
}

void ConverterView::chooseOutputFile()
{
    QString outputFile;

    outputFile = QFileDialog::getSaveFileName(this,titleChooseOutputFile);
    if(!outputFile.isNull()){
        m_outputFile->setText(outputFile);
    }
}
