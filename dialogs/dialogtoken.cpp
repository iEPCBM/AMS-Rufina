#include "dialogtoken.h"
#include "ui_dialogtoken.h"

DialogToken::DialogToken(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogToken)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogToken::~DialogToken()
{
    delete ui;
}

void DialogToken::setToken(const QString &strToken)
{
    m_strToken = strToken;
    displayToken();
}

inline void DialogToken::displayToken()
{
    ui->pteToken->setPlainText(m_strToken);
}
