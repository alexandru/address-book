#include "contactentry.h"

QDataStream& operator<<(QDataStream& os, const ContactEntry& ce)
{
    os << ce.getName() << ce.getPhoneNr();
    return os;
}

QDataStream& operator>>(QDataStream& is, ContactEntry& ce)
{
    is >> ce.name >> ce.phoneNr;
    return is;
}
