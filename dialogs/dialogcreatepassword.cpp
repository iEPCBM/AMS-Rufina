#include "dialogcreatepassword.h"
#include "ui_dialogcreatepassword.h"

DialogCreatePassword::DialogCreatePassword(QByteArray data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreatePassword),
    m_aes(data)
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
    if (ui->lePassword->text()!=ui->lePasswordConfirm->text()||ui->lePassword->text().isEmpty()) return false;
    return true;
}

QByteArray DialogCreatePassword::endcryptedData() const
{
    return m_endcryptedData;
}

void DialogCreatePassword::on_buttonBox_accepted()
{
    m_endcryptedData = m_aes.encryption(ui->lePassword->text());
}
