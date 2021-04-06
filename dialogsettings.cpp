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
    if (settingsHandler->isEncrypted()) {
        DialogPasswordEnter *dlgPswd = new DialogPasswordEnter(this);
        dlgPswd->exec();
        delete dlgPswd;
        dlgPswd = NULL;
    } else {
        DialogToken dlgToken(this);
        dlgToken.setToken(settingsHandler->getVkToken());
        dlgToken.exec();
    }
}

void DialogSettings::on_chbUseKeyCry_stateChanged(int arg1)
{
    if (arg1) {
        createPassword();
    } else {
        QMessageBox::question(this,"Вы уверены?","Вы уверены?");
    }
}

void DialogSettings::createPassword()
{
    DialogCreatePassword dlgCreatePswd(this);
    dlgCreatePswd.exec();
    if (dlgCreatePswd.result()==QDialog::Accepted) {
        ui->btEditKey->setEnabled(true);
        AESFacade aes(settingsHandler->getVkToken().toUtf8());
        QByteArray data = aes.encryption(dlgCreatePswd.getPassword());
        QString str64Data = QTextCodec::codecForMib(106)->toUnicode(data.toBase64());
        qDebug()<<data;
        qDebug()<<str64Data;

        //Test decryption
        qDebug()<<"Test decryption";
        AESFacade aes2(data);
        if (!aes2.decryption(dlgCreatePswd.getPassword())) {
            qDebug()<<aes2.getStrErr();
        } else {
            data = aes2.getDecryptedData();
            QString str64Data = QTextCodec::codecForMib(106)->toUnicode(data);
            qDebug()<<data;
            qDebug()<<str64Data;
        }

    }
}

void DialogSettings::on_buttonBoxAct_accepted()
{
    settingsHandler->setEncrypted(ui->chbUseKeyCry->isChecked());
    settingsHandler->setHsymbols(ui->leHSymbols->text());
    settingsHandler->setSignature(ui->leSignature->text());
    settingsHandler->save();
    emit saved();
}
