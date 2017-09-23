#ifndef TOOLS_H
#define TOOLS_H

#include <QApplication>
#include <QTranslator>

#include <QString>
#include <QDebug>
#include <QVariantMap>


class Tools
{
public:

    static QApplication *app;
    static QTranslator *translator;

    static void switchLanguage(QString language);


    static QMap<QString, QString> reverseMap(QMap<QString, QString> map);

    static QString paddingZero(qint64 i, int length = 2);

    /**
     * 输出空行，打印数据
     */
    static void pf();
    static void pf(int num, bool printNumber = true);
    static void pf(QVariantMap data);
    static void pf(QList<QVariantMap> data);
};

#endif // TOOLS_H
