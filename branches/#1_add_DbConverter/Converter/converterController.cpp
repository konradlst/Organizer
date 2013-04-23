#include "converterController.h"
#include "converterView.h"
#include "converterModel.h"

ConverterController::ConverterController(QWidget *parent) :
	QWidget(parent),
    m_model(new ConverterModel(this)),
    m_view(new ConverterView(this))
{
    m_view->show();
    connect(m_view,SIGNAL(convert()),m_model,SLOT(convert()));
    connect(m_view,SIGNAL(inputFileChanged(QString)),m_model,SLOT(setPathToLoad(QString)));
    connect(m_view,SIGNAL(outputFileChanged(QString)),m_model,SLOT(setPathToSave(QString)));
}
