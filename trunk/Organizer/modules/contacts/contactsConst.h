#ifndef CONTACTSCONST_H
#define CONTACTSCONST_H

class QObject;
class QString;

namespace
{
const QString DateFormat = "dd.MM.yyyy";
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

const QString phone = QObject::trUtf8("Phone :");
const QString email = QObject::trUtf8("Email :");
const QString site = QObject::trUtf8("Site :");
const QString skype = QObject::trUtf8("Skype :");

const QString name = QObject::trUtf8("Name :");
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

const QString phone = QObject::trUtf8("phone");
const QString email = QObject::trUtf8("email");
const QString site = QObject::trUtf8("site");
const QString skype = QObject::trUtf8("skype");

const QString name = QObject::trUtf8("name");
const QString department = QObject::trUtf8("department");
const QString post = QObject::trUtf8("post");
const QString address = QObject::trUtf8("address");
}

#endif // CONTACTSCONST_H
