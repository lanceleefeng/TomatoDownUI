#include <QtSql>

#include "db.h"
#include "init.h"

Init::Init()
    : m_success(false)
{

    QString connectionName = "tomato_";
    static DB& db = DB::instance(connectionName);

    QString sqlCreateCountDownTable = "create table if not exists t_count_down("

            ")";
    QString sqlCreateMusicTable = "create table if not exists t_music("

            ")";

    //"YYYY-MM-DD HH:MM:SS.SSS"
    // sqlite 不支持表注释、字段注释
    QString sqlCreateSettingsTable = "create table if not exists td_settings("
        "id integer PRIMARY KEY AUTOINCREMENT,"
        "uid integer default 0,"
        "language text,"
        "auto_start integer default 1,"
        "count_down integer default 1,"
        "auto_hide integer default 1,"
        "auto_hide_delay integer default 0,"
        "first_run_hide integer default 0,"
        "tomato_time integer default 25,"
        "tip_time integer default 3,"
        "break_time integer default 5,"
        "created_at text,"
        "updated_at text"
        ")";

    if(!db.exec(sqlCreateSettingsTable)){
        return;
    }


    QString sqlCreateTestTable = "create table if not exists td_test("
            "id integer PRIMARY KEY AUTOINCREMENT,"
            "uid integer default 0,"
            "test_auto_start integer default 1,"
            "countdown integer default 0,"
            "created_at text,"
            "updated_at text"
            ")";

    if(!db.exec(sqlCreateTestTable)){
        return;
    }
    m_success = true;
}

Init::~Init()
{

}

/**
 * 初始化是否成功
 * @return bool
 */
bool Init::succeed()
{
    //return false;
    return m_success;
}
