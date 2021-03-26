#include "dialogcreatepassword.h"
#include "ui_dialogcreatepassword.h"

DialogCreatePassword::DialogCreatePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreatePassword)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->lbIsPswdEqual->setStyleSheet("color: red;");
    ui->lePassword->setFocus();
}

DialogCreatePassword::~DialogCreatePassword()
{
    delete ui;
}

void DialogCreatePassword::on_lePasswordConfirm_textEdited(const QString &arg1)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(checkPassword());
    ui->lbIsPswdEqual->setText(checkPassword()?"":"Пароли не совпадают");
}
void DialogCreatePassword::on_lePassword_textEdited(const QString &arg1)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(checkPassword());
    ui->lbIsPswdEqual->setText(checkPassword()?"":"Пароли не совпадают");
}

bool DialogCreatePassword::checkPassword()
{
    if (ui->lePassword->text()!=ui->lePasswordConfirm->text()) return false;
    return true;
}

QString DialogCreatePassword::getPassword() const
{
    return m_strPassword;
}

void DialogCreatePassword::on_buttonBox_accepted()
{
    m_strPassword = ui->lePassword->text();
}
