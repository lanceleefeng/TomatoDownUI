#ifndef TOOLS_H
#define TOOLS_H

#include <QString>

class Tools
{
public:
    static QString paddingZero(qint64 i, int length = 2);
};

#endif // TOOLS_H