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

    QTranslator translator;

    Init init;
    if(!init.succeed()){
        QMessageBox::critical(0, Config::appName, QString("初始化失败！"));
        return -1;
    }

    UserModel::uid = uid;
    BaseModel::uid = uid;

    MainWindow w;
    //w.app = a;
    w.app = &a;
    w.translator = &translator;

    w.show();

    qDebug() << "语言：" << QLocale::system().name();

    if(w.newSetting["autoStart"].toBool()){
        w.on_pushButton_start_released();
    }

    return a.exec();
}
