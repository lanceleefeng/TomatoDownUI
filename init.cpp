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
    QString sqlCreateSettingsTable = "create table if not exists ts_settings("
            "id integer PRIMARY KEY AUTOINCREMENT,"
            "uid integer default 0,"
            "auto_start integer default 1,"
            "countdown integer default 0,"
            "created_at text,"
            "updated_at text"
            ")";

    if(!db.exec(sqlCreateSettingsTable)){
        return;
    }


    QString sqlCreateTestTable = "create table if not exists ts_test("
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


bool Init::succeed()
{
    return m_success;
}
