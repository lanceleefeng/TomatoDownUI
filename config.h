#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
//#include <QString>
#include <QVariant>

class Config
{
public:


    static bool isDebug;

    /**
     * 应用名称
     * （改用语言文件 appName 表示
     */
    static QString appName;
    static int width;
    static int height;

    //static QString defaultLanguage;

    static QMap<QString, QVariant> defaultSetting;

    static QString defaultTimerKey;

    static int progressMinValue;

    static QMap<QString, int> delayedTime;

};

#endif // CONFIG_H
