#ifndef SETTING_MODEL_H
#define SETTING_MODEL_H

#include "datetime.h"
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


    /**
     * 保存计时方式
     * 1 倒计时，0 正计时
     * @param countDown
     * @return
     */
    bool saveCountMode(int countDown);


    /**
     * 保存设置
     * 没有则添加记录，有则修改
     * @param data
     * @return
     */
    bool save(QVariantMap data);
};

#endif // SETTING_MODEL_H