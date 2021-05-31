#include "namedialog.h"
#include "ui_namedialog.h"

NameDialog::NameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &NameDialog::setName);
    connect(ui->lineEdit, &QLineEdit::textEdited,
            this, &NameDialog::update);

}

NameDialog::~NameDialog()
{
    delete ui;
}

void NameDialog::setName()
{
    m_name = ui->lineEdit->text();
}

void NameDialog::update()
{
    if (ui->lineEdit->text().isEmpty())
        ui->buttonBox->setEnabled(false);
    else
        ui->buttonBox->setEnabled(true);
}
