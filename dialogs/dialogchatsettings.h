#ifndef DIALOGCHATSETTINGS_H
#define DIALOGCHATSETTINGS_H

#include <QDialog>
#include <QMessageBox>

#include "vkApi/vkchat.h"

namespace Ui {
class DialogChatSettings;
}

class DialogChatSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatSettings(VkChat chat, QHash<uint8_t, VkChat>savedChats = QHash<uint8_t, VkChat>(), QWidget *parent = nullptr);
    explicit DialogChatSettings(uint8_t floor, VkChat chat, QWidget *parent = nullptr);
    ~DialogChatSettings();

    uint8_t floor() const;

    VkChat chat() const;

private slots:
    void on_buttonBox_accepted();

    void on_spinFloor_valueChanged(int arg1);

    void on_leChatTitle_textChanged(const QString &arg1);

    void accept();

private:
    Ui::DialogChatSettings *ui;
    VkChat m_chat;
    uint8_t m_floor;
    QHash<uint8_t, VkChat> m_savedChats;

    bool hasChatConflict();
};
#endif // DIALOGCHATSETTINGS_H
