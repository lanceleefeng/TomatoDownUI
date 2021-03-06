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

QVariantMap SettingModel::setting;
QVariantMap SettingModel::oldSetting;

QMap<QString, QString> SettingModel::fieldsMap = {
    {"auto_start", "autoStart"},
    {"count_down", "countDown"},
    {"auto_hide", "autoHide"},
    {"auto_hide_delay", "autoHideDelay"},
    {"first_run_hide", "firstRunHide"},
    {"tomato_time", "tomatoTime"},
    {"tip_time", "tipTime"},
    {"break_time", "breakTime"},
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



QVariantMap SettingModel::getSetting()
{
    if(setting.isEmpty()){
        setSetting();
    }
    return setting;
}

/**
 * 初始化时调用，从数据库和默认配置获取
 */
void SettingModel::setSetting()
{
    SettingModel model;
    QVariantMap where;
    where["uid"] = BaseModel::uid;

    setting = model.getOne(where);
    qDebug() << "数据库中的设置：";
    Tools::pf(setting);

    if(setting.isEmpty()){
        setting = Config::defaultSetting;
    }
}

/**
 * 由数据更新设置
 * 初始化后由交互操作调用
 * @param data
 */
void SettingModel::setSetting(QVariantMap data)
{
    setting = data;
}
