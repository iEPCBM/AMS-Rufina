#include "dialogsettings.h"
#include "ui_dialogsettings.h"

DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    settingsHandler = Settings::getInstance();
    ui->leHSymbols->setText(settingsHandler->getHsymbols());
    ui->leSignature->setText(settingsHandler->getSignature());
    ui->chbUseKeyCry->setChecked(settingsHandler->isEncrypted());
    ui->btEditKey->setEnabled(settingsHandler->isEncrypted());
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::on_btEditChatsList_clicked()
{
    DialogChatsList d_chats(this);
    d_chats.exec();
}

void DialogSettings::on_btShowToken_clicked()
{
    DialogToken dlgToken(this);
    if (settingsHandler->isEncrypted()) {
        DialogPasswordEnter dlgPswd(QByteArray::fromBase64(settingsHandler->getVkToken().toUtf8()), this);
        dlgPswd.exec();
        if (dlgPswd.isSuccessful()) {
            dlgToken.setToken(dlgPswd.getDecryptedData());
            dlgToken.exec();
        }
    } else {
        dlgToken.setToken(settingsHandler->getVkToken());
        dlgToken.exec();
    }
}

bool DialogSettings::createPassword()
{
    DialogCreatePassword dlgCreatePswd(settingsHandler->getVkToken().toUtf8(), this);
    if (dlgCreatePswd.exec()==QDialog::Accepted) {
        settingsHandler->setVkToken(QString::fromUtf8(dlgCreatePswd.endcryptedData().toBase64()));
        return true;
    }
    return false;
}

inline void DialogSettings::setEncryptedFlag(bool checked)
{
    settingsHandler->setEncrypted(checked);
    ui->chbUseKeyCry->setChecked(checked);
    ui->btEditKey->setEnabled(checked);
}

void DialogSettings::on_buttonBoxAct_accepted()
{
    settingsHandler->setEncrypted(ui->chbUseKeyCry->isChecked());
    settingsHandler->setHsymbols(ui->leHSymbols->text());
    settingsHandler->setSignature(ui->leSignature->text());
    settingsHandler->save();
    emit saved();
}

void DialogSettings::on_chbUseKeyCry_clicked(bool checked)
{
    if (checked) {
        setEncryptedFlag(createPassword());
    } else {
        if (QMessageBox::question(this,"Вы уверены?","Вы действительно хотите снять шифрование с токена?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes) {
            DialogPasswordEnter dlgPswd(QByteArray::fromBase64(settingsHandler->getVkToken().toUtf8()), this);
            dlgPswd.exec();
            if (dlgPswd.isSuccessful()) {
                settingsHandler->setVkToken(dlgPswd.getDecryptedData());
                setEncryptedFlag(false);
            } else {
                setEncryptedFlag(true);
            }
        } else {
            setEncryptedFlag(true);
        }
    }
}

void DialogSettings::on_btEditKey_clicked()
{
    DialogPasswordEnter dlgPswd(QByteArray::fromBase64(settingsHandler->getVkToken().toUtf8()), this);
    dlgPswd.exec();
    if (dlgPswd.isSuccessful()) {
        DialogCreatePassword dlgCreatePswd(dlgPswd.getDecryptedData(), this);
        if (dlgCreatePswd.exec()==QDialog::Accepted) {
            settingsHandler->setVkToken(QString::fromUtf8(dlgCreatePswd.endcryptedData().toBase64()));
        }
    }
}

void DialogSettings::on_btEditToken_clicked()
{
    if (settingsHandler->isEncrypted()) {
        DialogPasswordEnter dlgPswd(QByteArray::fromBase64(settingsHandler->getVkToken().toUtf8()), this);
        dlgPswd.exec();
        if (dlgPswd.isSuccessful()) {
            DialogCreatePassword dlgCreatePswd(dlgPswd.getDecryptedData(), this);
            if (dlgCreatePswd.exec()==QDialog::Accepted) {
                settingsHandler->setVkToken(QString::fromUtf8(dlgCreatePswd.endcryptedData().toBase64()));
            }
        }
    }
}
