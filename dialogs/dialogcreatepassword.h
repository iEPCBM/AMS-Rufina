#ifndef DIALOGCREATEPASSWORD_H
#define DIALOGCREATEPASSWORD_H

#include <QDialog>
#include <QPushButton>
#include "aesfacade.h"

namespace Ui {
class DialogCreatePassword;
}

class DialogCreatePassword : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreatePassword(QByteArray data, QWidget *parent = nullptr);
    ~DialogCreatePassword();

    QByteArray endcryptedData() const;

private slots:
    void on_lePasswordConfirm_textEdited(const QString &arg1);

    void on_lePassword_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::DialogCreatePassword *ui;
    inline bool checkPassword();

    AESFacade m_aes;
    QByteArray m_endcryptedData;
};

#endif // DIALOGCREATEPASSWORD_H
