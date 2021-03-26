#include "afterauthstrategy.h"

AfterAuthStrategy::AfterAuthStrategy(QString decryptedData)
{
    m_decryptedData = decryptedData;
}

void AfterAuthStrategy::setDecryptedData(const QString &decryptedData)
{
    m_decryptedData = decryptedData;
}
