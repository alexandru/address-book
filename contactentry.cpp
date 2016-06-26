#include "contactentry.h"

QDataStream& operator<<(QDataStream& os, const ContactEntry& ce)
{
    os << ce.getName() << ce.getPhoneNr() << ce.getEmail();
    return os;
}

QDataStream& operator>>(QDataStream& is, ContactEntry& ce)
{
    is >> ce.name >> ce.phoneNr >> ce.email;
    return is;
}
