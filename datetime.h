#ifndef DTAE_TIME_H
#define DTAE_TIME_H


#include <QString>

class DateTime {

public:

    static QString defaultFormat;

    static QString getTime();
    static QString getTime(QString format);

};


#endif //DTAE_TIME_H
