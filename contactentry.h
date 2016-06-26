#ifndef CONTACTENTRY_H
#define CONTACTENTRY_H

#import <QString>

struct ContactEntry
{
    ContactEntry() : name(""), phoneNr(""), email("") {}

    ContactEntry(QString name, QString phoneNr, QString email) :
        name(name), phoneNr(phoneNr), email(email) {}

    QString getName() const { return name; }
    QString getPhoneNr() const { return phoneNr; }
    QString getEmail() const { return email; }

    ContactEntry withName(QString name) const {
        return ContactEntry(name, phoneNr, email);
    }

    ContactEntry withPhoneNr(QString phoneNr) const {
        return ContactEntry(name, phoneNr, email);
    }

    ContactEntry withEmail(QString email) const {
        return ContactEntry(name, phoneNr, email);
    }

    bool operator==(const ContactEntry &l) const {
        return name == l.getName() && phoneNr == l.getPhoneNr() && email == l.getEmail();
    }

    bool operator!=(const ContactEntry &l) const {
        return name != l.getName() || phoneNr != l.getPhoneNr() || email != l.getEmail();
    }

    friend QDataStream& operator<<(QDataStream& os, const ContactEntry& ce);
    friend QDataStream& operator>>(QDataStream& is, ContactEntry& ce);

private:
    QString name;
    QString phoneNr;
    QString email;
};

#endif // CONTACTENTRY_H
