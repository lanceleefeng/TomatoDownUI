#include "mainwindow.h"

#include "basedata.h"
#include "tools.h"
#include "init.h"
#include "config.h"
#include "usermodel.h"
#include "basemodel.h"

#include <QApplication>
#include <QMessageBox>

static int uid = 1;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    Init init;
    if(!init.succeed()){
        QMessageBox::critical(0, Config::appName, QString("初始化失败！"));
        return -1;
    }

    UserModel::uid = uid;
    BaseModel::uid = uid;

    //Tools::pf(SettingModel::getSetting());
    SettingModel::setSetting();


    //QString language = "zh_cn";
    QString language = SettingModel::setting["language"].toString();
    Tools::app = &app;
    Tools::translator = &translator;

    Tools::switchLanguage(language);



    MainWindow window;
    window.show();

    qDebug() << "语言：" << QLocale::system().name();

    //if(window.newSetting["autoStart"].toBool()){
    if(SettingModel::setting["autoStart"].toBool()){
        window.on_pushButton_start_released();
    }

    return app.exec();
}
