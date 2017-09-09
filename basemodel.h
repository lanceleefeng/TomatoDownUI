
#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include "db.h"


class BaseModel
{
public:

    /**
     * 会员ID
     */
    static int uid;

    /**
     * 表名，实例化时加上前缀，使用时是全名
     */
    QString table;
    /**
     * 表前缀
     */
    static QString tablePrefix;
    /**
     * 表名是否是全名
     */
    static bool isFullName;

    /**
     * 获取表名，指定是否是全名（全名不加前缀）
     * @param tName
     * @param full
     * @return
     */
    static QString getTable(QString tName, bool full);

    /**
     * 表字段信息
     * 以表名为键保存
     */
    static QMap<QString, QMap<QString, int>>tableFields;

    BaseModel();

    /**
     * 两个有参构造函数，子类根据需要覆盖一个即可
     * @param tableName
     */
    BaseModel(QString tableName);
    BaseModel(QString tableName, bool isFullName);

    //static QMap<QString, int> getFields();
    /**
     * 获取表字段信息，加上tablePrefix
     * @param tableName
     * @return
     */
    static QMap<QString, int> getFields(QString tableName);

    /**
     * 获取表字段信息，指定是否是全名
     * @param tableName
     * @param isFullName
     * @return
     */
    static QMap<QString, int> getFields(QString tableName, bool isFullName);

    /**
     * 获取表字段信息，不直接使用，供getFields的重载使用
     * @param table
     * @return
     */
    static QMap<QString, int> getTableFields(QString table);

    /**
     * 设置表字段信息
     * @param table
     */
    static void setTableFields(QString table);


    /**
     * 根据ID获取一条记录
     * @param id
     * @return
     */
    QVariantMap getOne(int id);

    /**
     * 根据条件获取一条记录
     * @param where
     * @return
     */
    QVariantMap getOne(QVariantMap where);

    /**
     * 根据条件获取一条记录
     * @param where
     * @return
     */
    QVariantMap getOne(QString where);

    /**
     * 获取条例条件的所有记录
     * @param where
     * @return
     */
    QList<QVariantMap> getAll(QVariantMap where);

    /**
     * 获取一页记录
     * @param where
     * @param page
     * @param pageSize
     * @return
     */
    QList<QVariantMap> getPage(QVariantMap where, int page, int pageSize);

    /**
     * 添加数据
     * @param data
     * @return
     */
    bool add(QVariantMap data);

    /**
     * 修改数据
     * @param data
     * @param where
     * @return
     */
    bool update(QVariantMap data, QVariantMap where);

    /**
     * 修改数据
     * @param data
     * @param where
     * @return
     */
    bool update(QVariantMap data, QString where);

    /**
     * 删除数据
     * @param where
     * @return
     */
    bool del(QVariantMap where); // delete是关键字！

    /**
     * 删除数据
     * @param where
     * @return
     */
    bool del(QString where);

    /**
     * 封装where，由QVariantMap转换成QString
     * @param where
     * @return
     */
    QString getWhere(QVariantMap where);

};

#endif //BASE_MODEL_H
