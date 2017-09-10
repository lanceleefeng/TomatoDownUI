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

/**
 * 保存计时方式
 * 1 倒计时，0 正计时
 * @param countDown
 * @return
 */
bool SettingModel::saveCountMode(int countDown)
{
    QVariantMap data;
    data["countdown"] = countDown > 0 ? 1 : 0;
    return save(data);
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
        add(data);
    }else{
        qDebug() << "已有数据";
        where["id"] = row["id"];
        data["updated_at"] = time;
        update(data, where);
    }

    //qDebug() << "fk" << row["id"];
    return true;
}

