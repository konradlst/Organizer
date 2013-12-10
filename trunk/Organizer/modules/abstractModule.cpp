#include "abstractModule.h"

AbstractModule::AbstractModule(AbstractData *data, QWidget *parent)
    : QWidget(parent),
      m_data((data) ? data : (new AbstractData)),
      m_view(new AbstractView),
      m_dialog(new AbstractDialog)
{
}

AbstractView *AbstractModule::view()
{
    return m_view;
}

AbstractDialog *AbstractModule::dialog()
{
    return m_dialog;
}

AbstractData *AbstractModule::data()
{
    return m_data;
}
