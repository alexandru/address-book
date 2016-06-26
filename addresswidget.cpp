#include "adddialog.h"
#include "addresswidget.h"

#include <QtWidgets>

AddressWidget::AddressWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel(this);
    newAddressTab = new NewAddressTab(this);
    connect(newAddressTab, &NewAddressTab::sendDetails,
        this, &AddressWidget::addEntry);

    addTab(newAddressTab, "Address Book");

    setupTabs();
}


void AddressWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString phone = aDialog.phoneText->text();
        QString email = aDialog.emailText->text();

        addEntry(name, phone, email);
    }
}



void AddressWidget::addEntry(QString name, QString phone, QString email)
{
    QList<ContactEntry> list = table->getList();
    ContactEntry entry(name, phone, email);

    if (!list.contains(entry)) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, phone, Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, email, Qt::EditRole);
        removeTab(indexOf(newAddressTab));
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(name));
    }
}


void AddressWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString phone;
    QString email;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();

        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex phoneIndex = table->index(row, 1, QModelIndex());
        QVariant varPhone = table->data(phoneIndex, Qt::DisplayRole);
        phone = varPhone.toString();

        QModelIndex emailIndex = table->index(row, 2, QModelIndex());
        QVariant varAddr = table->data(emailIndex, Qt::DisplayRole);
        email = varAddr.toString();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Contact"));

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.phoneText->setText(phone);
    aDialog.emailText->setText(email);
}


void AddressWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }

    if (table->rowCount(QModelIndex()) == 0) {
        insertTab(0, newAddressTab, "Address Book");
    }
}


void AddressWidget::setupTabs()
{
    QStringList groups;
    groups << "All" << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);
        QString regExp = (i == 0) ? QString("^.*") : QString("^[%1].*").arg(str);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(0);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);

        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        tableView->setSortingEnabled(true);

        connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &AddressWidget::selectionChanged);

        addTab(tableView, str);
    }
}


void AddressWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QList<ContactEntry> entries = table->getList();
    QDataStream in(&file);
    in >> entries;

    if (entries.isEmpty()) {
        QMessageBox::information(this, tr("No contacts in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    } else {
        for (int i=0; i<entries.size(); ++i) {
            ContactEntry p = entries.at(i);
            addEntry(p.getName(), p.getPhoneNr(), p.getEmail());
        }
    }
}


void AddressWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QList<ContactEntry> entries = table->getList();
    QDataStream out(&file);
    out << entries;
}
