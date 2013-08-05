#ifndef CGFINANCEVIEW_H
#define CGFINANCEVIEW_H

class QDoubleSpinBox;
class QFrame;
class QDateEdit;
class QWidget;

namespace View
{
QDoubleSpinBox *DoubleSpinBox();
QFrame *Line();
QDateEdit *DateWidget();
QWidget *TodayList();
}

#endif // CGFINANCEVIEW_H
