#ifndef AFTERAUTHSTRATEGY_H
#define AFTERAUTHSTRATEGY_H
#include <QString>

//NOTE: interface
class AfterAuthStrategy
{
public:
    AfterAuthStrategy(QString decryptedData);

    virtual void execute()=0;

    void setDecryptedData(const QString &decryptedData);

private:
    QString m_decryptedData;
};

#endif // AFTERAUTHSTRATEGY_H
