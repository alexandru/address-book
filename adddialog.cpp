#include "adddialog.h"

#include <QtWidgets>

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
{
    nameLabel = new QLabel("Name");
    //addressLabel = new QLabel("Address");
    phoneLabel = new QLabel("Phone no.");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    nameText = new QLineEdit;
    phoneText = new QLineEdit;
    //addressText = new QTextEdit;

    QGridLayout *gLayout = new QGridLayout;
    //gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

//    gLayout->addWidget(addressLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
//    gLayout->addWidget(addressText, 1, 1, Qt::AlignLeft);

    gLayout->addWidget(phoneLabel, 1, 0);
    gLayout->addWidget(phoneText, 1, 1);


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Add a Contact"));
}
