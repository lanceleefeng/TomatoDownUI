#include "mainwindow.h"

#include "basedata.h"
#include "init.h"
#include "config.h"
#include "usermodel.h"
#include "basemodel.h"

#include <QApplication>
#include <QMessageBox>

static int uid = 1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Init init;
    if(!init.succeed()){
        QMessageBox::critical(0, Config::appName, QString("初始化失败！"));
        return -1;
    }

    //qDebug() << "使用命名空间和别名的ENUM：" << TickState::Count;
    //qDebug() << "直接访问？：" << BaseData::TickState_::Break;
    //qDebug() << "直接访问，不用命名空间？：" << TickState_::Break; // 报错


    UserModel::uid = uid;
    BaseModel::uid = uid;

    MainWindow w;
    w.show();

    if(w.newSetting["autoStart"].toBool()){
        w.on_pushButton_start_released();
    }

    return a.exec();
}
