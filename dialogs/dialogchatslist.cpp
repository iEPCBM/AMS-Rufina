/*
 *  AMS Rufina - automated message delivery program
 *  Copyright (C) 2021 Rishat D. Kagirov (iEPCBM)
 *
 *     This file is part of AMS Rufina.
 *
 *  AMS Rufina is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "dialogchatslist.h"
#include "ui_dialogchatslist.h"

DialogChatsList::DialogChatsList(QHash<uint8_t, VkChat> chats, QString token, bool isEncrypted, QString iv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatsList)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_IV = iv;
    setToken(token, isEncrypted);
    m_chats = chats;
    ui->tableChats->setFocusPolicy(Qt::NoFocus);
    updateChatsTable();
}

DialogChatsList::~DialogChatsList()
{
    delete ui;
}

void DialogChatsList::setToken(const QString &token, const bool &isEncrypted)
{
    m_token = token;
    m_isEncrypted = isEncrypted;
}

void DialogChatsList::on_btnAddChat_clicked()
{
    DialogAddChat dlgAddChat(m_token, m_isEncrypted, m_IV, this);
    dlgAddChat.setAddedChats(m_chats);
    int resultDlg = dlgAddChat.exec();
    if (resultDlg == QDialog::Accepted) {
        ui->tableChats->setRowCount(0);
        m_chats = dlgAddChat.getAddedChats();
        updateChatsTable();
    }
}

void DialogChatsList::onEditChat(uint8_t floor, VkChat chat)
{
    DialogChatSettings dlgChatSettings(floor, chat, this);
    int resultDlg = dlgChatSettings.exec();
    if (resultDlg == QDialog::Accepted) {
        uint8_t n_floor = dlgChatSettings.floor();
        VkChat n_chat = dlgChatSettings.chat();
        if (floor==n_floor) {
            m_chats[floor] = n_chat;
        }
        else if (m_chats.contains(n_floor)) {
            QMessageBox::StandardButton btClicked =
                    QMessageBox::question(this, "Поменять беседы местами?", "Для " + QString::number(n_floor) +
                                  " этажа уже существует беседа \"" + m_chats[n_floor].getTitle() +
                                  "\". Поменять беседы \"" + n_chat.getTitle() + "\" и \"" +
                                  m_chats[n_floor].getTitle() + "\" местами?");

            if (btClicked == QMessageBox::Yes) {
                VkChat t_chat = m_chats[n_floor];
                m_chats[n_floor] = n_chat;
                m_chats[floor] = t_chat;
            }
        } else {
            m_chats[n_floor] = n_chat;
            m_chats.remove(floor);
        }
        updateChatsTable();
    }
}

void DialogChatsList::onDeleteChat(uint8_t floor, VkChat chat)
{
    QMessageBox::StandardButton btClicked = QMessageBox::question(this, "Удалить беседу?", "Вы действительно хотите удалить беседу \"" + chat.getTitle() + "\" из списка?");
    if (btClicked == QMessageBox::Yes) {
        m_chats.remove(floor);
        updateChatsTable();
    }
}

QHash<uint8_t, VkChat> DialogChatsList::getChats() const
{
    return m_chats;
}

void DialogChatsList::updateChatsTable()
{
    QList<uint8_t> keys = m_chats.keys();

    QTableWidget* table = ui->tableChats;
    table->setRowCount(0);

    foreach (uint8_t floor, keys) {
        VkChat chat = m_chats[floor];
        table->insertRow (ui->tableChats->rowCount());
        int lastRow = ui->tableChats->rowCount()-1;
        updateChatsTableRow(lastRow, floor, chat);

        ChatActionButton *btEditChat = new ChatActionButton("Изменить", chat, ui->tableChats);
        ChatActionButton *btDeleteChat = new ChatActionButton("Удалить", chat, ui->tableChats);
        btEditChat->setFloor(floor);
        btEditChat->setRow(lastRow);
        btDeleteChat->setFloor(floor);
        btDeleteChat->setRow(lastRow);
        QIcon iconEdit;
        iconEdit.addFile(QString::fromUtf8(FILEPATH_ICON_EDIT), QSize(), QIcon::Normal, QIcon::Off);
        btEditChat->setIcon(iconEdit);
        QIcon iconDelete;
        iconDelete.addFile(QString::fromUtf8(FILEPATH_ICON_DELETE), QSize(), QIcon::Normal, QIcon::Off);
        btDeleteChat->setIcon(iconDelete);

        QWidget *widgetWrapper = new QWidget();
        QHBoxLayout *layoutBt = new QHBoxLayout(widgetWrapper);
        QSpacerItem *vertSpacerHeader = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QSpacerItem *vertSpacerFooter= new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layoutBt->addItem(vertSpacerHeader);
        layoutBt->addWidget(btEditChat);
        layoutBt->addWidget(btDeleteChat);

        layoutBt->addItem(vertSpacerFooter);
        ui->tableChats->setCellWidget(
                 lastRow,
                 3,
                 widgetWrapper);

        connect(btEditChat, SIGNAL(cabtClickedFloor(uint8_t, VkChat)), this, SLOT(onEditChat(uint8_t, VkChat)));
        connect(btDeleteChat, SIGNAL(cabtClickedFloor(uint8_t, VkChat)), this, SLOT(onDeleteChat(uint8_t, VkChat)));

        ui->tableChats->resizeRowToContents(lastRow);
        ui->tableChats->resizeColumnsToContents();
    }
    ui->tableChats->sortByColumn(2, Qt::AscendingOrder);
}

void DialogChatsList::updateChatsTableRow(uint row, uint8_t floor, VkChat chat)
{
    QTableWidgetItem *cellItem = new QTableWidgetItem(QString::number(chat.getId()));
    cellItem->setFlags(cellItem->flags()^Qt::ItemIsEditable);
    ui->tableChats->setItem (row, 0, cellItem);

    cellItem = new QTableWidgetItem(chat.getTitle());
    cellItem->setFlags(cellItem->flags()^Qt::ItemIsEditable);
    ui->tableChats->setItem  (row, 1, cellItem);

    cellItem = new QTableWidgetItem(QString::number(floor));
    cellItem->setFlags(cellItem->flags()^Qt::ItemIsEditable);
    ui->tableChats->setItem  (row, 2, cellItem);
}

void DialogChatsList::on_btnDeleteAllChats_clicked()
{
    QMessageBox::StandardButton btClicked = QMessageBox::question(this, "Удалить все беседы?", "Вы действительно хотите удалить все беседы из списка?");
    if (btClicked == QMessageBox::Yes) {
        m_chats.clear();
        updateChatsTable();
    }
}
