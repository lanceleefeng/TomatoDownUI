#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
//#include <QString>
#include <QVariant>

class Config
{
public:

    static QString appName;
    static QMap<QString, QVariant> defaultSetting;

    static QString defaultTimerKey;

    static bool isDebug;


};

#endif // CONFIG_H
