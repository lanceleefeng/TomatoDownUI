#ifndef SETTING_MODEL_H
#define SETTING_MODEL_H


#include "datetime.h"
#include "tools.h"
#include "config.h"
#include "db.h"

#include "basemodel.h"



class SettingModel : public BaseModel
{

public:
    typedef BaseModel super;
    SettingModel();
    ~SettingModel();


    /**
     * 表名
     */
    static QString tableName;
    //static bool isFullName;

    static QVariantMap setting;
    static QVariantMap oldSetting;

    // 不搞什么时间戳设置，手动加
    //bool timestamp = true;
    //QMap<QString, QString> timestampFields;

    /**
     * 软删除
     * @param countDown
     * @return
     */
    //bool softDelete = true;


    //bool add(QVariantMap data);

    static QMap<QString, QString> fieldsMap;


    /**
     * 查询一条数据
     * @param where
     * @return
     */

    QVariantMap getOne(QString where);
    QVariantMap getOne(QVariantMap where);

    /**
     * 保存设置
     * 没有则添加记录，有则修改
     * @param data
     * @return
     */
    bool save(QVariantMap data);

    static QVariantMap getSetting();
    static void setSetting();
    static void setSetting(QVariantMap data);

};

#endif // SETTING_MODEL_H