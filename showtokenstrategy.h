#ifndef SHOWTOKENSTRATEGY_H
#define SHOWTOKENSTRATEGY_H

#include "afterauthstrategy.h"

class ShowTokenStrategy : AfterAuthStrategy
{
public:
    ShowTokenStrategy(QString strData);
    void execute();
};

#endif // SHOWTOKENSTRATEGY_H
