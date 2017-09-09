#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


#include <QList>
#include <QUrl>
#include <QMap>



#include "db.h"

// 实现DB单例模式，但Instance方法在cpp文件中实现一直报错
// 最终采用了混合实现：
// 单例相关的函数都在db.h中实现，
// 其他代码在db.h中定义，在db.cpp中实现


/*
// static DB::Instance()
static DB& DB::instance()
{
    static DB db;
    return db;
}
*/

QString DB::standardBinding(QString binding)
{
    if(binding.at(0) != QChar(':')){
        binding = ":"+binding;
    }
    return binding;
}

void DB::test()
{
    qDebug() << "DB singleton test";
}

QString DB::error()
{
    //return conn.lastError();
    //return conn.lastError().text();
    return errMsg;
}

// void DB::setConn(QString connectionName = "")
void DB::setConn(QString connectionName)
{
    QString driver = "QSQLITE";

    QString dbPath;
    dbPath = QCoreApplication::applicationDirPath();
    //dbPath = "E:";

    //QString dbName = "test.db";
    //QString dbName = "setttings.db";
    QString dbName = "../setttings.db";

    QString dbFullPath = dbPath + "/" + dbName;


    //qDebug() << "db path: " << dbFullPath;
    //qDebug() << __FUNCTION__;

    if(connectionName.size() == 0){
        //db.conn = QSqlDatabase::addDatabase(driver);
        conn = QSqlDatabase::addDatabase(driver);
    }else{
        conn = QSqlDatabase::addDatabase(driver, "conn_" + connectionName);
    }

    //for MySQL
    //conn.setHostName(host);
    //conn.setDatabaseName(database);
    //conn.setUserName(username);
    //conn.setPassword(password);

    // for SQLite
    conn.setDatabaseName(dbFullPath);


    if(!conn.open()){
        errCode = 1001;
        errMsg = "错误：" + QString(errCode) + "; 连接数据库失败：" + conn.lastError().text();
    }
}


bool DB::exec(QString sql)
{
    bool result = q->exec(sql);
    if(!result){
        errMsg = q->lastError().text();
    }
    return result;
}

bool DB::exec(QString sql, QVariantMap data)
{
    QList<QMap<QString, QVariant>> datas;
    datas << data;
    return exec(sql, datas);
}

bool DB::exec(QString sql, QList<QVariantMap> datas)
{

    //qDebug() << __FILE__ << ": " << __LINE__;
    //qDebug() << sql;

    QMap<QString, QVariantList> bindVals;
    QVariantList vals;

    //不必手动遍历第一个元素找到keys，原来QMap封装的有获取keys的方法
    //http://doc.qt.io/qt-5/qmap.html#keys
    QList<QString> bindKeys = datas[0].keys();

    /*
    //java style iterator
    //http://doc.qt.io/qt-5/qmap.html#details

    QVariantMap data = datas[0];
    QMapIterator<QString, QVariant> i(data);
    while(i.hasNext()){
        i.next();
        bindKeys << i.key();
        qDebug() << "keys: " << i.key() << ": " << i.value();
        //bindVals[i.key()] = NULL;
    }*/

    QMap<QString, QVariant> item;
    foreach(item, datas){
            QMap<QString, QVariant>::const_iterator ir = item.constBegin();
            while(ir != item.constEnd()){
                bindVals[ir.key()] << ir.value();
                qDebug() << ir.key() << ": " << ir.value();
                //ir++;
                ++ir;
            }
        }

    //query.prepare(sql);
    //q.prepare(sql);
    q->prepare(sql);

    QString key;
    foreach(key, bindKeys){
            //qDebug() << "key: " << key;
            //q->bindValue(":" + key, bindVals[key]);
            q->bindValue(standardBinding(key), bindVals[key]);
            //q->bindValue(DB::standardBinding(key), bindVals[key]);
    }

    /*
    // STL-style iterator
    QMap<QString, QVariantList>::const_iterator it3 = bindVals.constBegin();
    QVariant val;
    while(it3 != bindVals.constEnd()){
        qDebug() << "key: " << it3.key();
        vals = it3.value();
        foreach(val, vals){
                 qDebug() << "val: " << val;
            }
        ++it3;
    }
    */

    if(!q->execBatch()){
        q->finish();
        return false;
    }
    q->finish();
    return true;
}


QList<QVariantList> DB::fetch()
{
    QList<QVariantList> datas;
    while(q->next()){
        QVariantList data;
        qint32 index = 0;
        while(true){
            QVariant value = q->value(index);
            if(!value.isValid()){
                break;
            }
            data << value;
            ++index;
        }
        datas << data;
    }

    return datas;
}

QList<QVariantList> DB::query(QString sql)
{

    q->exec();

    /*
    QList<QVariantList> datas;
    while(q->next()){
        QVariantList data;
        qint32 index = 0;
        while(true){
            QVariant value = q->value(index);
            if(!value.isValid()){
                break;
            }
            data << value;
            ++index;
        }
        datas << data;
    }
    */
    QList<QVariantList> datas = fetch();
    return datas;
}

QList<QVariantList> DB::query(QString sql, bool placeholder, QVariantMap bindings)
{

    q->prepare(sql);

    QMap<QString, QVariant>::const_iterator i = bindings.constBegin();
    while(i != bindings.constEnd()){
        q->bindValue(standardBinding(i.key()), i.value());
        ++i;
    }

    q->execBatch();
    QList<QVariantList> datas = fetch();
    q->finish();

    return datas;
}

QList<QVariantList> DB::query(QString sql, bool placeholder, QList<QString> bindings)
{

    q->prepare(sql);

    QString binding;
    foreach(binding, bindings){
        q->addBindValue(binding);
    }

    q->execBatch();
    QList<QVariantList> datas = fetch();
    q->finish();

    return datas;
}

QList<QVariantMap> DB::fetch(QStringList keys)
{
    //qDebug() << __FUNCTION__;
    QList<QVariantMap> datas;
    qint32 length = keys.length();
    //qDebug() << "key length: " << length;
    while(q->next()){
        QVariantMap data;
        QString key;
        for(int i=0; i<length; ++i){
            key = keys.at(i); //list的at()比[]快
            //qDebug() << "fetch key: " << key;
            data[key] = q->value(i); // 用name读取数据不如用索引高效
        }
        datas << data;
        //datas.append(data);
    }
    return datas;
}

/**
 * 查询数据，指定返回键名
 * @param sql 查询语句
 * @param keys 键名列表
 * @return QList<QVariantMap> (等价于QList<QMap<QString, QVariant>>）
 */

QList<QVariantMap> DB::query(QString sql, QStringList keys)
{

    // 返回数据的key: 必须与select的顺序一致
    // 可以少，不可以多，中间不能跳过(只能取前n个或全部)

    q->exec(sql);

    /*

    //QList<QMap<QString, QVariant>> datas;
    QList<QVariantMap> datas;
    qint32 length = keys.length();

    //while(q.next()){
    while(q->next()){
        QVariantMap data;
        QString key;
        for(int i=0; i < length; ++i){
            key = keys.at(i); //list的at()比[]快
            data[key] = q->value(i).toString();
        }
        datas.append(data);
    }*/

    QList<QVariantMap> datas = fetch(keys);
    q->finish();
    return datas;
}

QList<QVariantMap> DB::query(QString sql, QStringList keys, QVariantMap bindings)
{

    q->prepare(sql);

    QMap<QString, QVariant>::const_iterator i = bindings.constBegin();
    while(i != bindings.constEnd()){
        //绑定不能绑定单个值，必须用列表
        //q->bindValue(standardBinding(i.key()), i.value());
        QVariantList binding;
        binding << i.value();
        q->bindValue(standardBinding(i.key()), binding);
        ++i;
    }

    q->execBatch();
    QList<QVariantMap> datas = fetch(keys);
    q->finish();
    return datas;
}

QList<QVariantMap> DB::query(QString sql, QStringList keys, QVariantList bindings)
{

    q->prepare(sql);

    QVariant binding;
    foreach(binding, bindings){
            //单独绑定一个值绑定不了，必须用list
            //q->addBindValue(binding);
            QVariantList bd;
            bd << binding;
            q->addBindValue(bd);
    }

    q->execBatch();

    QList<QVariantMap> datas = fetch(keys);
    q->finish();
    return datas;
}

