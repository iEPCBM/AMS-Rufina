#ifndef DIALOGCHATSLIST_H
#define DIALOGCHATSLIST_H

#include <QDialog>
#include "dialogaddchat.h"

namespace Ui {
class DialogChatsList;
}

class DialogChatsList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatsList(QWidget *parent = nullptr);
    ~DialogChatsList();

private slots:
    void on_btnAddChat_clicked();

private:
    Ui::DialogChatsList *ui;
};

#endif // DIALOGCHATSLIST_H
