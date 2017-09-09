
#include <QDateTime>

#include "datetime.h"


QString DateTime::defaultFormat = "yyyy-MM-dd hh:mm:ss";

QString DateTime::getTime()
{
    return getTime(defaultFormat);
}
QString DateTime::getTime(QString format)
{
    if(format.isEmpty()){
        format = defaultFormat;
    }
    QString timeStr = QDateTime::currentDateTime().toString(format);
    return timeStr;
}

