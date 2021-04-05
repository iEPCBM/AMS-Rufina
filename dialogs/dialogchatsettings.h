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
    explicit DialogChatSettings(VkChat *chat, QWidget *parent = nullptr);
    ~DialogChatSettings();

private:
    Ui::DialogChatSettings *ui;
    VkChat *m_chat;
};

#endif // DIALOGCHATSETTINGS_H
