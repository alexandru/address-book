#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::TableModel(QList<ContactEntry> list, QObject *parent)
    : QAbstractTableModel(parent)
{
    entries = list;
}



int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return entries.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}



QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= entries.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        ContactEntry entry = entries.at(index.row());

        if (index.column() == 0)
            return entry.getName();
        else if (index.column() == 1)
            return entry.getPhoneNr();
        else if (index.column() == 2)
            return entry.getEmail();
    }
    return QVariant();
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Phone Number");
            case 2:
                return tr("Email");
            default:
                return QVariant();
        }
    }
    return QVariant();
}



bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        ContactEntry entry(" ", " ", " ");
        entries.insert(position, entry);
    }

    endInsertRows();
    return true;
}



bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        entries.removeAt(position);
    }

    endRemoveRows();
    return true;
}
//! [5]

//! [6]
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        ContactEntry p = entries.value(row);

        if (index.column() == 0)
            p = p.withName(value.toString());
        else if (index.column() == 1)
            p = p.withPhoneNr(value.toString());
        else if (index.column() == 2)
            p = p.withEmail(value.toString());
        else
            return false;

        entries.replace(row, p);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}
//! [6]

//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]
QList<ContactEntry> TableModel::getList()
{
    return entries;
}
//! [8]
