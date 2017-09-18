#include <QtSql>
#include <QSqlTableModel>

#include "datetime.h"

#include "db.h"
#include "settingmodel.h"

/**
 * 表名
 */
QString SettingModel::tableName = "settings";
//bool SettingModel::isFullName = true;

QMap<QString, QString> SettingModel::fieldsMap = {
    {"auto_start", "autoStart"},
    {"count_down", "countDown"},
    {"auto_hide", "autoHide"},
    {"auto_hide_delay", "autoHideDelay"},
    {"first_run_hide", "firstRunHide"},
};


/**
 * 构造函数
 */
SettingModel::SettingModel()
{
    getFields(tableName);
    table = getTable(tableName, isFullName);
}

SettingModel::~SettingModel()
{
}


QVariantMap SettingModel::getOne(QString where)
{
    QVariantMap data = super::getOne(where);
    data = BaseModel::dataTransform(data, fieldsMap);
    return data;
}

QVariantMap SettingModel::getOne(QVariantMap where)
{
    where = BaseModel::dataTransform(where, fieldsMap, true);

    QVariantMap data = super::getOne(where);
    data = BaseModel::dataTransform(data, fieldsMap);
    return data;
}

/**
 * 保存设置
 * 没有则添加记录，有则修改
 * @param data
 * @return
 */
bool SettingModel::save(QVariantMap data)
{
    QVariantMap where;
    QString time = DateTime::getTime();

    where["uid"] = uid;
    QVariantMap row = getOne(where);

    if(row.isEmpty()){
        qDebug() << "没有数据";
        data["uid"] = uid;
        data["created_at"] = time;
        data["updated_at"] = time;

        // 虽然QMap可以直接打印，但还是有必要再封装一下，输出没有格式，不易读
        //qDebug() << data;
        Tools::pf(data);

        //data = BaseModel::dataTransform(data, fieldsMap);
        data = BaseModel::dataTransform(data, fieldsMap, true);
        Tools::pf(data);

        add(data);

    }else{
        qDebug() << "已有数据";
        where["id"] = row["id"];
        data["updated_at"] = time;

        data = BaseModel::dataTransform(data, fieldsMap, true);

        Tools::pf(data);

        update(data, where);
    }

    //qDebug() << "fk" << row["id"];
    return true;
}

