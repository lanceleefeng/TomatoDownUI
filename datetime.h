#ifndef DTAE_TIME_H
#define DTAE_TIME_H


#include <QString>

#include <QDateTime>


class DateTime {

public:

    static QString defaultFormat;

    static QString getTime();
    static QString getTime(QString format);

    //static QDateTime timeOffset(QDateTime time = 0, qint64 seconds);

    static qint64 getSecondsSince(QDateTime time);



};


#endif //DTAE_TIME_H
