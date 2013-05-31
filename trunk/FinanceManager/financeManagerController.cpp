#include "financeManagerController.h"
#include "financeManagerView.h"
#include "financeManagerModel.h"

FinanceManagerController::FinanceManagerController(QWidget *parent) :
    QWidget(parent),
    m_view(new FinanceManagerView()),
    m_model(new FinanceManagerModel())
{
    m_view->show();
}
