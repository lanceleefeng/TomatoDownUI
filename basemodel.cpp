
#include "db.h"
#include "basemodel.h"

int BaseModel::uid;

bool BaseModel::isFullName = false;

QString BaseModel::tablePrefix = "td_";


QMap<QString, QString> BaseModel::fieldsMap;

QMap<QString, QMap<QString, int>> BaseModel::tableFields;
/**
 * 无参构造函数
 */
BaseModel::BaseModel()
{
    //setTableInfo();
}
/**
 * 指定表名的构造函数
 * 使用默认前缀，由BaseModel::tablePrefix指定
 * @param tableName
 */
BaseModel::BaseModel(QString tableName){
    //qDebug() << "table name: " << tableName;

    //this->table = tableName;
    table = tablePrefix + tableName;
    //qDebug() << "table name: " << table;

    setTableFields(table);

}

QVariantMap BaseModel::getOne(QString where)
{
    QVariantMap row;

    QSqlTableModel model(Q_NULLPTR, DB::instance().conn);
    model.setTable(table);
    if(!where.isEmpty()){
        model.setFilter(where);
    }
    bool res = model.select();
    if(!res){
        return row;
    }
    int count = model.rowCount();
    //qDebug() << "条数：" << count;

    for(int i=0; i<count; i++){
        QSqlRecord record = model.record(i);
        int fieldsNum = record.count();
        for(int j=0; j<fieldsNum; j++){
            row[record.fieldName(j)] = record.value(j);
        }
        break;
    }
    return row;
}
QVariantMap BaseModel::getOne(QVariantMap where)
{
    if(where.isEmpty()){
        return getOne("");
    }

    QString wh = getWhere(where);
    return getOne(wh);
}


bool BaseModel::add(QVariantMap data)
{
    if(data.isEmpty()){
        return false;
    }

    QSqlTableModel model(Q_NULLPTR, DB::instance().conn);
    model.setTable(table);
    QMap<QString, int> fields = getFields(table, true);

    if(fields.isEmpty()){
        qDebug() << "shit, fields not obtained";
        return false;
    }

    int row = 0;
    model.insertRows(row, 1);

    QMap<QString, QVariant>::const_iterator i = data.constBegin();
    while(i != data.constEnd()){
        QString key = i.key();
        int index = fields[key];
        QString val = i.value().toString();

        model.setData(model.index(row, index), val);
        ++i;
    }

    bool res = model.submitAll();
    //qDebug() << model.lastError();
    return res;

}


bool BaseModel::update(QVariantMap data, QVariantMap where)
{
    QString w = getWhere(where);
    return update(data, w);
}

bool BaseModel::update(QVariantMap data, QString where)
{
    QSqlTableModel model(Q_NULLPTR, DB::instance().conn);
    model.setTable(table);
    model.setFilter(where);

    model.select();
    int num = model.rowCount();
    QMap<QString, int> fields = getFields(table, true);


    // model.setRecord的方式可以在for循环结束后再model.submitAll()
    for(int i=0; i<num; i++){
        int row = i;
        QSqlRecord record = model.record(row);
        QMap<QString, QVariant>::const_iterator d = data.constBegin();
        while(d != data.constEnd()){

            QString key = d.key();
            QString val = d.value().toString();
            if(!fields.contains(key)){
                ++d;
                continue;
            }
            int col = fields[key];
            //model.setData(model.index(row, col), val);
            record.setValue(col, val);

            ++d;
        }
        model.setRecord(row, record);
        //model.submitAll(); // 原来每修改一条都要提交，在for循环结束后再提交只能修改第一个..
        //model.setData(model.index(i, k), v);
    }

    model.submitAll();
    return true;

}

bool BaseModel::del(QVariantMap where)
{
    QString w = getWhere(where);
    return del(w);
}

bool BaseModel::del(QString where)
{
    if(where.isEmpty()){
        return false;
    }
    QSqlTableModel model(Q_NULLPTR, DB::instance().conn);
    model.setTable(table);
    model.setFilter(where);
    model.select();

    int num = model.rowCount();

    if(num == 0){
        return true;
    }


    //model.submitAll();
    //return res;

    /*while(num > 0){
        model.setFilter(where);
        model.select();
        model.removeRows(0, 1);
        model.submitAll();
        num = model.rowCount();
    }*/

    // 删除与文档不一致：

    //bool res = model.removeRows(0, num); // 无效
    // 循环中删除一条并提交，有效
    for(int i=0; i<num; i++){
        model.removeRows(i, 1);
        //model.submitAll();
    }
    model.submitAll();

    return true;
}

QString BaseModel::getWhere(QVariantMap where)
{
    if(where.isEmpty()){
        return "";
    }

    //QMap<QString, int> fields = getFields(table);
    QMap<QString, int> fields = getFields(table, true);

    QString w;
    bool first = true;
    QMap<QString, QVariant>::const_iterator con = where.constBegin();

    //qDebug() << "条件：";
    while(con != where.constEnd()){
        QString key = con.key();
        QString val = con.value().toString();
        //qDebug() << key << ": \t" << val;

        if(!fields.contains(key)){
            ++con;
            continue;
        }
        if(!first){
            w += " AND " + key + "=" + val;
        }else{
            w += key + "=" + val;
        }

        first = false;
        ++con;
    }

    qDebug() << "where: " << w;
    return w;
}

/**
 * 获取表字段列表，使用默认前缀
 *
 * @param QString tableName
 * @return
 */
QMap<QString, int> BaseModel::getFields(QString tableName)
{
    //QString table = getTableName();
    //QString table = BaseModel::getTableName();
    QString table = BaseModel::tablePrefix + tableName;
    //qDebug() << "table got in BaseModel: " << table;

    return BaseModel::getTableFields(table);
}

/**
 * 获取表名，指定是否是全名（全名不加前缀）
 * @param tName
 * @param full
 * @return
 */
QString BaseModel::getTable(QString tName, bool full)
{
    QString t = !full ? tablePrefix + tName : tName;
    return t;
}

/**
 * 获取表字段信息
 * @param tableName
 * @param isFullName
 * @return
 */
QMap<QString, int> BaseModel::getFields(QString tableName, bool isFullName)
{
    if(isFullName){
        return BaseModel::getTableFields(tableName);
    }else{
        return BaseModel::getFields(tableName);
    }
};
/**
 * 获取表段列信息
 * @param QString table 不再处理前缀问题，直接使用表名
 * @return
 */
QMap<QString, int> BaseModel::getTableFields(QString table)
{
    if(BaseModel::tableFields[table].isEmpty()){
        BaseModel::setTableFields(table);
    }
    return BaseModel::tableFields[table];
}

/**
 * 设置表字段信息
 * @param table
 */
void BaseModel::setTableFields(QString table)
{
    if(!tableFields[table].isEmpty()){
        return;
    }
    //qDebug() << "table got in BaseModel: " << table;

    QString sql = "PRAGMA table_info("+table+")";
    QStringList keys;
    keys << "cid" << "name";

    static DB& db = DB::instance();
    QList<QVariantMap> tableInfoList = db.query(sql, keys); // QList<QMap<QString, QVariant>>

    QMap<QString, int> tableInfo;
    QVariantMap field;
            foreach(field, tableInfoList){
            tableInfo[field["name"].toString()] = field["cid"].toInt();
        }

    //return tableInfo;
    //QMap<QString, QMap<QString, int>> fields;
    //fields[table] = tableInfo;
    //return fields;
    tableFields[table] = tableInfo;
}

QVariantMap BaseModel::dataTransform(QVariantMap data, QMap<QString, QString> keys, bool reverse)
{
    QVariantMap res;

    if(reverse){
        keys = Tools::reverseMap(keys);
    }

    QMap<QString, QVariant>::const_iterator i = data.constBegin();
    QString key;
    QVariant val;
    while(i != data.constEnd()){
        key = i.key();
        val = i.value();
        //qDebug() << key << ": " << val;
        key = keys.contains(key) ? keys[key] : key;
        res[key] = val;
        ++i;
    }
    return res;
}


QList<QVariantMap> BaseModel::dataTransform(QList<QVariantMap> data, QMap<QString, QString> keys, bool reverse)
{


}

