#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateMsgPreview();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QCheckBox* MainWindow::getFloorChk(int floor)
{
    switch (floor) {
    case 2:
        return this->ui->chkSecondFloor;
        break;
    case 3:
        return this->ui->chkThirdFloor;
        break;
    case 4:
        return this->ui->chkFourthFloor;
        break;
    case 5:
        return this->ui->chkFifthFloor;
        break;
    }
    return nullptr;
}


void MainWindow::on_actionSettings_triggered()
{
    DialogSettings dSettings(this);
    dSettings.exec();
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAboutProgram_triggered()
{
    QMessageBox::about(this,"О программе", "Система автоматизированной отправки сообщений Руфина");
}

void MainWindow::on_btCheckAllFloors_clicked()
{
    for (auto i=2; i<=5; i++) {
        getFloorChk(i)->setChecked(true);
    }
}

void MainWindow::on_btSend_clicked()
{
    MessageAssembler masm(ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    QHash<QString, QString> query;
    query["random_id"]=QString::number(VkApi::getRandomId(masm.assembly(),VK_API_MULTICHAT_BASE_ID+1));
    query["peer_id"]=QString::number(VK_API_MULTICHAT_BASE_ID+1);
    query["message"]=masm.assembly();
    VkApi api(this, "***REMOVED***");
    connect(&api, SIGNAL(requestFinished(QNetworkReply*)), this, SLOT(VkApiRequestFinished(QNetworkReply*)));
    api.sendRequest("messages.send", query);
}

void MainWindow::updateMsgPreview()
{
    MessageAssembler masm(ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    ui->txtedPreview->setText(masm.assembly());
}

void MainWindow::on_ptxtedMessageText_textChanged()
{
    updateMsgPreview();
}

void MainWindow::on_chkAddAttentionStr_stateChanged(int arg1)
{
    updateMsgPreview();
}

void MainWindow::on_chkPingAll_stateChanged(int arg1)
{
    updateMsgPreview();
}

void MainWindow::on_chkAddSignature_stateChanged(int arg1)
{
    updateMsgPreview();
}

void MainWindow::VkApiRequestFinished(QNetworkReply *r)
{
    qDebug()<<"F!";
    qDebug()<<r->readAll();
}
