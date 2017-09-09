#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QList>
#include <QUrl>
#include <QMap>

// #include <QDebug>

// 单例模式
// http://blog.yangyubo.com/2009/06/04/best-cpp-singleton-pattern/#id7

/*
class Singleton {
public:
    static Singleton& Instance() {
        static Singleton theSingleton;
        return theSingleton;
    }

    // more (non-static) functions here
    
private:
    Singleton();                            // ctor hidden
    Singleton(Singleton const&);            // copy ctor hidden
    Singleton& operator=(Singleton const&); // assign op. hidden
    ~Singleton();                           // dtor hidden
};
*/

class DB
{
public:

    static DB& instance(QString connectionName = "tomato")
    {
        static DB db;
        //qDebug() << "db.conn.isOpen(): " << db.conn.isOpen();

        //if(db.conn.isValid()) { // isValid()表示驱动是否有效
        if(!db.conn.isOpen()) { // isOpen()连接是否打开
            db.setConn(connectionName);
        }

        //qDebug() << "db.conn.isOpen(): " << db.conn.isOpen();

        db.q = new QSqlQuery(db.conn);
        return db;
    }

    QString standardBinding(QString binding);
    
    void test();
    QString error();

    //QString connName = "conn_tomato";
    //static QString connName;

    bool exec(QString sql);
    bool exec(QString sql, QVariantMap data);
    bool exec(QString sql, QList<QVariantMap> datas);

    bool exec(QString sql, QVariantList data);
    bool exec(QString sql, QList<QVariantList> datas);


    QList<QVariantList> fetch();
    QList<QVariantMap> fetch(QStringList keys);


    QList<QVariantList> query(QString sql);
    QList<QVariantList> query(QString sql, bool placeholder, QVariantMap bindings);

    // 这样写用起来还是容易出错，不如增加到3个参数，
    // 如果要绑定参数，必须用3个参数的，且绑定参数是第个3
    // 这样string类型的list，都可以用QStringList了

    //QStringList 是 QListIterator<QString> 的简写，而不是 QList<QString>
    //QList<QVariantList> query(QString sql, QList<QString> bindings);
    QList<QVariantList> query(QString sql, bool placeholder, QList<QString> bindings);


    //http://doc.qt.io/qt-5/qstringlist.html
    //QList<QMap<QString, QVariant>> query(QString sql, QStringList keys);
    QList<QVariantMap> query(QString sql, QStringList keys);
    QList<QVariantMap> query(QString sql, QStringList keys, QVariantMap bindings);
    //QList<QVariantMap> query(QString sql, QStringList keys, QStringList bindings);
    QList<QVariantMap> query(QString sql, QStringList keys, QVariantList bindings);

    QSqlDatabase conn;

    qint32 errCode = 0;

    QString errMsg = "";


private:
    DB(){}
    DB(DB const&){}
    DB& operator=(DB const&);
    ~DB(){}

    void setConn(QString connectionName = "");

    //QSqlQuery query;
    QSqlQuery* q;
};

#endif // DB_H
