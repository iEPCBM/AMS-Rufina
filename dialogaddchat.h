#ifndef DIALOGADDCHAT_H
#define DIALOGADDCHAT_H

#include <QDialog>
#include "vkApi/vkapi.h"
#include "vkApi/vkchat.h"

namespace Ui {
class DialogAddChat;
}

class DialogAddChat : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddChat(QWidget *parent = nullptr);
    ~DialogAddChat();

public slots:
    void onChatGot();

private slots:
    void on_btStartStopFind_clicked();

private:
    Ui::DialogAddChat *ui;
    bool m_isSearching = false;
    void findChats();
    void addChatToTable(VkChat chat);
    QList<VkChat> m_listChats;

};

#endif // DIALOGADDCHAT_H
