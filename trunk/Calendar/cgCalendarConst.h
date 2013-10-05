#ifndef CGCALENDARCONST_H
#define CGCALENDARCONST_H

#include <QPair>

namespace Calendar
{
enum TaskType { Task = 0, Holiday };
enum DurationType { Day = 0, Week, Mounth, Year };
typedef QPair<int, DurationType> Duration;
}

#endif // CGCALENDARCONST_H
