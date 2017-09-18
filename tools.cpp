#include "tools.h"


QMap<QString, QString> Tools::reverseMap(QMap<QString, QString> map)
{
    if(map.isEmpty()){
        return map;
    }
    QMap<QString, QString> newMap;
    QMap<QString, QString>::const_iterator i = map.constBegin();
    while(i != map.constEnd()){
        newMap[i.value()] = i.key();
        ++i;
    }
    return newMap;
};

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

void Tools::pf(QVariantMap data)
{
    if(!data.isEmpty()){
        QMap<QString, QVariant>::const_iterator i = data.constBegin();
        while(i != data.constEnd()){
            qDebug() << i.key() << ":\t" << i.value();
            ++i;
        }
    }else{
        qDebug() << "empty map";
    }
    qDebug() << "\n";
}