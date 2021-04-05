#include "dialogchatconfirmation.h"
#include "ui_dialogchatconfirmation.h"

DialogChatConfirmation::DialogChatConfirmation(VkChat *chat, QString token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatConfirmation),
    m_msgDelivery(token, this)
{
    ui->setupUi(this);
    ui->leCodeInput->setValidator(new QRegExpValidator(QRegExp("^[a-fA-F0-9]+$"), this));
    m_chat = chat;
    generateCode();
}

DialogChatConfirmation::~DialogChatConfirmation()
{
    delete ui;
}

QByteArray DialogChatConfirmation::crc32b(QByteArray message)
{
    uint32_t byte, crc, mask, len;

    len = message.length();
    crc = 0xFFFFFFFF;

    for (auto i = 0; --len; i++) {
       byte = static_cast<uint32_t>(message.at(i));
       crc = crc ^ byte;
       for (auto j = 0; j < 8; j++) {
          mask = -(crc & 1);
          crc = (crc >> 1) ^ (0xEDB88320 & mask);
       }
    }
    crc = ~crc;
    QByteArray retVal(reinterpret_cast<char*>(&crc), sizeof(crc));
    return retVal;
}

void DialogChatConfirmation::generateCode()
{
    m_data2hash = QDate::currentDate().toString(Qt::ISODate)+" "
            +QTime::currentTime().toString(Qt::ISODateWithMs)
            +QString::number(VK_API_MULTICHAT_BASE_ID+m_chat->getId())
            +CRC_SALT;
    qDebug()<<m_data2hash;
    QByteArray crcHash = crc32b(m_data2hash.toUtf8()).toHex();
    qDebug()<<crcHash;
    m_msgDelivery.sendMessage(VK_API_MULTICHAT_BASE_ID+m_chat->getId(), STR_CONFIRMATION_PREAMBLE+QString::fromUtf8(crcHash));
}

bool DialogChatConfirmation::isConfirmated() const
{
    return m_isConfirmated;
}

void DialogChatConfirmation::on_btSendAgain_clicked()
{
    generateCode();
}

void DialogChatConfirmation::on_buttonBox_accepted()
{
    QByteArray checkHash = crc32b(m_data2hash.toUtf8()).toHex();
    if (ui->leCodeInput->text().toLower()!=QString::fromUtf8(checkHash)) {
        QMessageBox::StandardButton bt = QMessageBox::warning(this, "Ошибка", "Код не совпадает", QMessageBox::Retry|QMessageBox::Ok);
        if (bt==QMessageBox::Retry){
            ui->leCodeInput->clear();
            generateCode();
        }
        else {this->close();}
    } else {
        m_isConfirmated = true;
        this->close();
    }
}
