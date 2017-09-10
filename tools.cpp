#include "tools.h"


/**
 * 补0
 * @param i
 * @param length
 * @return
 */
QString Tools::paddingZero(qint64 i, int length)
{
    QString s = QString("%1").arg(i, length, 10, QLatin1Char('0'));
    return s;
}