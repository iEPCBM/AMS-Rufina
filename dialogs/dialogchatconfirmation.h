#ifndef DIALOGCHATCONFIRMATION_H
#define DIALOGCHATCONFIRMATION_H

#include <QDialog>
#include <QDebug>
#include <QTime>
#include <QDate>
#include "vkApi/vkchat.h"
#include "vkApi/vkmessagedelivery.h"

#define CRC_SALT "Руфина, прости меня. Ты мне правда нравишься."
#define STR_CONFIRMATION_PREAMBLE "Код подтверждения: "

namespace Ui {
class DialogChatConfirmation;
}

class DialogChatConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatConfirmation(VkChat *chat, QString token, QWidget *parent = nullptr);
    ~DialogChatConfirmation();

    bool isConfirmated() const;

private slots:
    void on_btSendAgain_clicked();

    void on_buttonBox_accepted();
    void accept(){}
private:
    Ui::DialogChatConfirmation *ui;
    QByteArray crc32b(QByteArray message);
    VkChat *m_chat;
    VkMessageDelivery m_msgDelivery;
    QString m_data2hash;
    void generateCode();
    bool m_isConfirmated = false;
};

#endif // DIALOGCHATCONFIRMATION_H
