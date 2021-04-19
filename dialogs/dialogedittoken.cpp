#include "dialogedittoken.h"
#include "ui_dialogedittoken.h"

DialogEditToken::DialogEditToken(QString token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditToken)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_token = token;
    ui->pteToken->setPlainText(m_token);
}

DialogEditToken::~DialogEditToken()
{
    delete ui;
}

void DialogEditToken::on_buttonBox_accepted()
{
    m_token = ui->pteToken->toPlainText().trimmed();
}

QString DialogEditToken::token() const
{
    return m_token;
}
