#ifndef CONTACTENTRY_H
#define CONTACTENTRY_H

#import <QString>

struct ContactEntry
{
    ContactEntry() : name(""), phoneNr("") {}

    ContactEntry(QString name, QString phoneNr) :
        name(name), phoneNr(phoneNr) {}

    QString getName() const { return name; }
    QString getPhoneNr() const { return phoneNr; }

    ContactEntry withName(QString name) const {
        return ContactEntry(name, phoneNr);
    }

    ContactEntry withPhoneNr(QString phoneNr) const {
        return ContactEntry(name, phoneNr);
    }

    bool operator==(const ContactEntry &l) const {
        return name == l.getName() && phoneNr == l.getPhoneNr();
    }

    bool operator!=(const ContactEntry &l) const {
        return name != l.getName() || phoneNr != l.getPhoneNr();
    }

    friend QDataStream& operator<<(QDataStream& os, const ContactEntry& ce);
    friend QDataStream& operator>>(QDataStream& is, ContactEntry& ce);

private:
    QString name;
    QString phoneNr;
};

#endif // CONTACTENTRY_H
