#ifndef DIALOGPASSWORDENTER_H
#define DIALOGPASSWORDENTER_H

#include <QDialog>
#include <QMessageBox>
#include "aesfacade.h"

namespace Ui {
class DialogPasswordEnter;
}

class DialogPasswordEnter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPasswordEnter(QByteArray encryptedData, QWidget *parent = nullptr);
    ~DialogPasswordEnter();

    QString getPassword();

    bool isSuccessful() const;

    QByteArray getDecryptedData() const;

    QByteArray getEncryptedData() const;
    void setEncryptedData(const QByteArray &encryptedData);

private slots:
    void on_buttonBox_accepted();
    void accept(){}

private:
    Ui::DialogPasswordEnter *ui;
    QByteArray m_encryptedData;
    QString m_pswd;
    AESFacade m_aes;
    QByteArray m_decryptedData;
    bool m_isSuccessful = false;
};

#endif // DIALOGPASSWORDENTER_H
