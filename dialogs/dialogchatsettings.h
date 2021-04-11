#ifndef DIALOGCHATSETTINGS_H
#define DIALOGCHATSETTINGS_H

#include <QDialog>
#include "vkApi/vkchat.h"

namespace Ui {
class DialogChatSettings;
}

class DialogChatSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatSettings(VkChat chat, QWidget *parent = nullptr);
    ~DialogChatSettings();

    uint8_t floor() const;

    VkChat chat() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogChatSettings *ui;
    VkChat m_chat;
    uint8_t m_floor;
};
#endif // DIALOGCHATSETTINGS_H
