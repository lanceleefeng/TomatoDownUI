
#include "datetime.h"

QString DateTime::defaultFormat = "yyyy-MM-dd hh:mm:ss";


QString DateTime::getTime()
{
    return getTime(defaultFormat);
}

/**
 * 获取指定格式的时间字符串
 * @param format
 * @return
 */
QString DateTime::getTime(QString format)
{
    if(format.isEmpty()){
        format = defaultFormat;
    }
    QString timeStr = QDateTime::currentDateTime().toString(format);
    return timeStr;
}

/**
 * 计算时间偏移（秒数）
 * 没有必要
 * @param QDateTime time
 * @param qint64 seconds
 * @return QDateTime
 */
//QDateTime DateTime::timeOffset(QDateTime time, qint64 seconds)
//{
//    return time.addSecs(seconds);
//}


/**
 * 获取从某个开始开始的秒数
 * @param time
 * @return
 */
qint64 DateTime::getSecondsSince(QDateTime time)
{
    qint64 milliSeconds = QDateTime::currentMSecsSinceEpoch() - time.toMSecsSinceEpoch();
    return milliSeconds/1000;
}


