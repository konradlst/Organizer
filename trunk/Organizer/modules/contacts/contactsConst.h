#ifndef CONTACTSCONST_H
#define CONTACTSCONST_H

class QObject;
class QChar;
class QString;
class QStringList;

namespace
{
const QChar Comma = ',';
const QChar Separator = ';';
const QString Today = "today";
const QString DateFormat = "dd.MM.yyyy";
const QStringList ChannelTypes = QObject::trUtf8("Phone;Email;Skype;Site").split(Separator);
}

namespace Title
{
const QString contact = QObject::trUtf8("Contact Dialog");
const QString address = QObject::trUtf8("Address Dialog");
const QString channel = QObject::trUtf8("Channel Dialog");
const QString company = QObject::trUtf8("Company Dialog");
}

namespace Label
{
const QString alias = QObject::trUtf8("Alias :");
const QString surName = QObject::trUtf8("Surname :");
const QString otherName = QObject::trUtf8("Other name :");
const QString birthday = QObject::trUtf8("Birthday :");
const QString description = QObject::trUtf8("Description :");

const QString country = QObject::trUtf8("Country :");
const QString city = QObject::trUtf8("City :");
const QString street = QObject::trUtf8("Street :");
const QString home = QObject::trUtf8("Home :");
const QString apartment = QObject::trUtf8("Apartment :");

const QString type = QObject::trUtf8("Type :");
const QString subType = QObject::trUtf8("SubType :");
const QString value = QObject::trUtf8("Value :");

const QString name = QObject::trUtf8("Name :");
const QString phone = QObject::trUtf8("Phone :");
const QString department = QObject::trUtf8("Department :");
const QString post = QObject::trUtf8("Post :");
const QString address = QObject::trUtf8("Address :");
const QString dateIn = QObject::trUtf8("Date in :");
const QString dateOut = QObject::trUtf8("Date out :");
}

namespace Placeholder
{
const QString alias = QObject::trUtf8("alias");
const QString surName = QObject::trUtf8("surname");
const QString otherName = QObject::trUtf8("other name");

const QString country = QObject::trUtf8("country");
const QString city = QObject::trUtf8("city");
const QString street = QObject::trUtf8("street");
const QString home = QObject::trUtf8("home");
const QString apartment = QObject::trUtf8("apartment");

const QString value = QObject::trUtf8("value");
const QString subType = QObject::trUtf8("subType");

const QString name = QObject::trUtf8("name");
const QString phone = QObject::trUtf8("phone");
const QString department = QObject::trUtf8("department");
const QString post = QObject::trUtf8("post");
const QString address = QObject::trUtf8("address");
}

#endif // CONTACTSCONST_H
