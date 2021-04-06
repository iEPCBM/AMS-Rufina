#include "dialogpasswordenter.h"
#include "ui_dialogpasswordenter.h"

DialogPasswordEnter::DialogPasswordEnter(QByteArray encryptedData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPasswordEnter),
    m_aes(encryptedData)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogPasswordEnter::~DialogPasswordEnter()
{
    delete ui;
}

void DialogPasswordEnter::on_buttonBox_accepted()
{
    if (m_aes.decryption(ui->lePswd->text())) {
        m_decryptedData = m_aes.getDecryptedData();
        m_isSuccessful = true;
        this->close();
    } else {
        QMessageBox::StandardButton bt =
                QMessageBox::critical(this, "Ошибка", "Неправильный пароль!", QMessageBox::Retry|QMessageBox::Ok);
        if (bt == QMessageBox::Ok) {
            this->close();
        } else {
            ui->lePswd->clear();
            ui->lePswd->setFocus();
        }
    }
}

QByteArray DialogPasswordEnter::getEncryptedData() const
{
    return m_encryptedData;
}

void DialogPasswordEnter::setEncryptedData(const QByteArray &encryptedData)
{
    m_encryptedData = encryptedData;
}

QByteArray DialogPasswordEnter::getDecryptedData() const
{
    return m_decryptedData;
}

bool DialogPasswordEnter::isSuccessful() const
{
    return m_isSuccessful;
}
