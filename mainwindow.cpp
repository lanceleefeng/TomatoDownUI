#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "config.h"
#include "datetime.h"
#include "usermodel.h"
#include "settingmodel.h"

#include <QDebug>

//#include <QIcon>
//#include <QPixmap>
//#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //, defaultTimerKey("walking")
    , tickState(TickState::Init)
{

    ui->setupUi(this);


    setWindowTitle(Config::appName);

    QDesktopWidget *desktop = QApplication::desktop();
    qDebug() << desktop->width() << "*"<< desktop->height();

    QRect availableRect = desktop->availableGeometry();

    qDebug() << "available: " << availableRect.width() << "*" << availableRect.height();

    int geoX = (availableRect.width() - Config::width)/2;
    //int geoY = (availableRect.height() - height)/2;


    //setGeometry: Unable to set geometry 22x22+400+190 on QWidgetWindow/'TomatoClassWindow'.
    //Resulting geometry:  128x22+400+190 (frame: 8, 31, 8, 8, custom margin: 0, 0, 0, 0, minimum size: 22x22, maximum size: 16777215x16777215).

    //setGeometry(geoX, 150, 500, 400);
    //setGeometry(geoX, 200, 500, 400);
    setGeometry(geoX, 200, Config::width, Config::height);
    setWindowTitle(tr("番茄倒计时"));



    defaultTimerKey = Config::defaultTimerKey;

    ui->lineEdit_time->setText("25");
    ui->lineEdit_tipTime->setText("3");
    ui->lineEdit_breakTime->setText("5");

    setControlButtonVisibility();

    SettingModel settingModel;
    QVariantMap setting = settingModel.getOne(QString("uid=%1").arg(UserModel::uid));

    if(setting.isEmpty()){
        setting = Config::defaultSetting;
    }

    QMap<QString, QVariant>::const_iterator iSetting = Config::defaultSetting.constBegin();
    while(iSetting != Config::defaultSetting.constEnd()){
        qDebug() << iSetting.key() << iSetting.value();
        //QString sKey = iSetting.key();
        //QVariant sVal = iSetting.value();
        //newSetting[sKey] = sVal;
        //oldSetting[sKey] = sVal;

        ++iSetting;
    }

    newSetting = setting;
    oldSetting = setting;

    //if(newSetting["autoStart"].toBool()){
    //    ui->checkBox_autoStart->setChecked(true);
    //}
    ui->checkBox_autoStart->setChecked(newSetting["autoStart"].toBool());
    ui->checkBox_countDown->setChecked(newSetting["countDown"].toBool());
    ui->checkBox_autoHide->setChecked(newSetting["autoHide"].toBool());
    ui->checkBox_singleWindow->setChecked(newSetting["singleWindow"].toBool());


    taskbarButton = new QWinTaskbarButton(this);
    taskbarProgress = taskbarButton->progress();
    taskbarProgress->setVisible(true);

    initiated = true;


}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * 开始按钮
 */
void MainWindow::on_pushButton_start_released()
{

    //tickState = TickState::Count;
    setTickState(TickState::Count);

    taskbarButton->setWindow(this->windowHandle());

    collectTimeInfo();

    row["startTime"] = QDateTime::currentDateTime();
    //row["endTime"] = DateTime::timeOffset(row["startTime"].toDateTime(), row["time"].toInt()*60);
    row["endTime"] = row["startTime"].toDateTime().addSecs(row["time"].toInt()*60);

    ui->label_endTime->setText(row["endTime"].toDateTime().toString(DateTime::defaultFormat));

    createTimer(defaultTimerKey);
    timer[defaultTimerKey]->start(1000);
    tick();
    tickHook();

}


/**
 * 重新计时
 */
void MainWindow::on_pushButton_restart_released()
{
    qDebug() << "重新计时";

    setTickState(TickState::Count);
    timeConsumed[defaultTimerKey] = 0;

    collectTimeInfo();

    row["startTime"] = QDateTime::currentDateTime();
    row["endTime"] = row["startTime"].toDateTime().addSecs(row["time"].toInt()*60);
    ui->label_endTime->setText(row["endTime"].toDateTime().toString(DateTime::defaultFormat));

    createTimer(defaultTimerKey);
    timer[defaultTimerKey]->stop();
    timer[defaultTimerKey]->start(1000);
    tick();
    tickHook();

}

/**
 * 休息
 */
void MainWindow::on_pushButton_break_released()
{

    if(tickState == TickState::Count){
        timeConsumed[defaultTimerKey] += DateTime::getSecondsSince(row["startTime"].toDateTime());
    }

    setTickState(TickState::Break);

    row["breakTime"] = ui->lineEdit_breakTime->text();

    row["startTime"] = QDateTime::currentDateTime();
    row["endTime"] = row["startTime"].toDateTime().addSecs(row["breakTime"].toInt()*60);
    ui->label_endTime->setText(row["endTime"].toDateTime().toString(DateTime::defaultFormat));

    createTimer(defaultTimerKey);
    timer[defaultTimerKey]->stop();
    timer[defaultTimerKey]->start(1000);
    tick();
    tickHook();
}

/**
 * 暂停
 */
void MainWindow::on_pushButton_pause_released()
{
    timeConsumed[defaultTimerKey] += DateTime::getSecondsSince(row["startTime"].toDateTime());
    qDebug() << "已耗时：" << timeConsumed[defaultTimerKey];

    setTickState(TickState::Pause);
    row["startTime"] = QDateTime::currentDateTime();
    tick();
}


/**
 * 继续
 */
void MainWindow::on_pushButton_continue_released()
{
    setTickState(TickState::Count);
    row["startTime"] = QDateTime::currentDateTime();

    row["endTime"] = row["startTime"].toDateTime().addSecs(row["time"].toInt()*60 - timeConsumed[defaultTimerKey]);
    ui->label_endTime->setText(row["endTime"].toDateTime().toString(DateTime::defaultFormat));

    tick();
    tickHook();
}

/**
 * 停止
 */
void MainWindow::on_pushButton_stop_released()
{
    if(tickState == TickState::Count){
        timeConsumed[defaultTimerKey] += DateTime::getSecondsSince(row["startTime"].toDateTime());
    }
    setTickState(TickState::Stop);
    row["startTime"] = QDateTime::currentDateTime();
    ui->label_endTime->setText("-");

    tick();
}


/**
 * 创建计时器
 * @param timerKey
 */
void MainWindow::createTimer(QString timerKey)
{
    if(!timer.contains(timerKey)){
        timer[timerKey] = new QTimer();
        connect(timer[timerKey], &QTimer::timeout, this, &MainWindow::tick);
    }
}

/**
 * 计时程序
 */
void MainWindow::tick()
{
    //qDebug() << __FUNCTION__ << "...";

    qint64 seconds = DateTime::getSecondsSince(row["startTime"].toDateTime());
    qint64 remainingSeconds = 0, totalSeconds = 0;


    //qint64 sec = seconds

    qint64 time = row["time"].toInt();
    qint64 tipTime = row["tipTime"].toInt();
    qint64 breakTime = row["breakTime"].toInt();

    double min;


    QString progressInfo;
    qint64 progressValue;

    qint64 consumedSeconds = timeConsumed[defaultTimerKey];
    //qint64 titleConsumedMin, titleConsumedSec;
    QString titleConsumedMin, titleConsumedSec;


    qint64 iconMin, iconSec;
    QString titleMin, titleSec;

    progressValue = seconds;
    iconMin = seconds/60;
    iconSec = seconds%60;

    titleMin = Tools::paddingZero(iconMin);
    titleSec = Tools::paddingZero(iconSec);

    if(newSetting["countDown"].toBool()){

        remainingSeconds = time*60 - consumedSeconds;

        titleConsumedMin = Tools::paddingZero(remainingSeconds/60);
        titleConsumedSec = Tools::paddingZero(remainingSeconds%60);

        switch(tickState){

            case TickState::Count:

                totalSeconds = time*60;
                seconds += consumedSeconds;


                if(seconds >= totalSeconds){
                    //setTickState(TickState::Break);
                    on_pushButton_break_released();
                    tick();
                    return;
                }
                remainingSeconds = totalSeconds - seconds;
                progressValue = remainingSeconds;

                iconState = remainingSeconds > tipTime*60 ? IconState::Normal : IconState::Stop;

                iconMin = ceil((double)remainingSeconds/60);
                iconSec = remainingSeconds%60;

                titleMin = Tools::paddingZero(remainingSeconds/60);
                titleSec = Tools::paddingZero(iconSec);

                progressInfo = QString("%1:%2/%3").arg(titleMin).arg(titleSec).arg(time);

                //qDebug() << "iconMin: " << iconMin;
                //qDebug() << "progressInfo: " << progressInfo;

                break;
            case TickState::Break:
                totalSeconds = breakTime*60;
                remainingSeconds = breakTime*60 - seconds;
                progressValue = remainingSeconds;

                if(seconds >= totalSeconds){
                    setTickState(TickState::Overtime);
                    tick();
                    return;
                }

                iconState = IconState::Pause;

                iconMin = ceil((double)remainingSeconds/60);
                iconSec = remainingSeconds%60;

                titleMin = Tools::paddingZero(remainingSeconds/60);
                titleSec = Tools::paddingZero(iconSec);

                if(consumedSeconds >= time*60){
                    progressInfo = QString("休息 %1:%2/%3 - %4").arg(titleMin).arg(titleSec).arg(breakTime).arg(time);
                }else{
                    progressInfo = QString("休息 %1:%2/%3 - %4:%5/%6").arg(titleMin).arg(titleSec)
                        .arg(breakTime).arg(titleConsumedMin).arg(titleConsumedSec).arg(time);
                }

                break;
            case TickState::Overtime:
                iconState = IconState::Normal;
                if(consumedSeconds >= time*60){
                    progressInfo = QString("超时 %1:%2/%3 - %4").arg(titleMin).arg(titleSec).arg(breakTime).arg(time);
                }else{
                    progressInfo = QString("超时 %1:%2/%3 - %4:%5/%6").arg(titleMin).arg(titleSec)
                        .arg(breakTime).arg(titleConsumedMin).arg(titleConsumedSec).arg(time);
                }

                break;
            case TickState::Pause:
            case TickState::Stop:
            default:
                QString strState = tickState == TickState::Pause ? "暂停" : "停止";
                iconState = IconState::Normal;
                progressInfo = QString("%1 %2:%3 - %4:%5/%6").arg(strState).arg(titleMin).arg(titleSec)
                    .arg(titleConsumedMin).arg(titleConsumedSec).arg(time);

                break;
        }
    }else{

        remainingSeconds = time*60 - consumedSeconds;

        titleConsumedMin = Tools::paddingZero(seconds/60);
        titleConsumedSec = Tools::paddingZero(seconds%60);

        switch(tickState){

            case TickState::Count:

                totalSeconds = time*60;
                seconds += consumedSeconds;

                if(seconds >= totalSeconds){
                    //setTickState(TickState::Break);
                    on_pushButton_break_released();
                    tick();
                    return;
                }
                remainingSeconds = totalSeconds - seconds;
                progressValue = seconds;

                iconState = remainingSeconds > tipTime*60 ? IconState::Normal : IconState::Stop;

                iconMin = ceil((double)seconds/60);
                iconSec = seconds%60;

                progressInfo = QString("%1:%2/%3").arg(titleMin).arg(titleSec).arg(time);

                //qDebug() << "iconMin: " << iconMin;
                //qDebug() << "progressInfo: " << progressInfo;

                break;
            case TickState::Break:
                totalSeconds = breakTime*60;
                remainingSeconds = breakTime*60 - seconds;

                if(seconds >= totalSeconds){
                    setTickState(TickState::Overtime);
                    tick();
                    return;
                }

                iconState = IconState::Pause;

                iconMin = ceil((double)seconds/60);
                iconSec = remainingSeconds%60;

                if(consumedSeconds >= time*60){
                    progressInfo = QString("休息 %1:%2/%3 - %4").arg(titleMin).arg(titleSec).arg(breakTime).arg(time);
                }else{
                    progressInfo = QString("休息 %1:%2/%3 - %4:%5/%6").arg(titleMin).arg(titleSec)
                        .arg(breakTime).arg(titleConsumedMin).arg(titleConsumedSec).arg(time);
                }

                break;
            case TickState::Overtime:
                iconState = IconState::Normal;
                if(consumedSeconds >= time*60){
                    progressInfo = QString("超时 %1:%2/%3 - %4").arg(titleMin).arg(titleSec).arg(breakTime).arg(time);
                }else{
                    progressInfo = QString("超时 %1:%2/%3 - %4:%5/%6").arg(titleMin).arg(titleSec)
                        .arg(breakTime).arg(titleConsumedMin).arg(titleConsumedSec).arg(time);
                }

                break;
            case TickState::Pause:
            case TickState::Stop:
            default:
                QString strState = tickState == TickState::Pause ? "暂停" : "停止";
                iconState = IconState::Normal;
                progressInfo = QString("%1 %2:%3 - %4:%5/%6").arg(strState).arg(titleMin).arg(titleSec)
                    .arg(titleConsumedMin).arg(titleConsumedSec).arg(time);

                break;
        }

    }


    QString windowTitle = QString("%1 - %2").arg(progressInfo).arg(Config::appName);
    setWindowTitle(windowTitle);
    ui->label_progress->setText(progressInfo);


    setOverlayIcon(iconMin);
    setTaskbarProgress(iconState, progressValue, totalSeconds);

}

/**
 * 设置状态
 * @param state
 */
void MainWindow::setTickState(TickState state)
{
    tickState = state;
    setControlButtonVisibility();
}

/**
 * 设置控制按钮可见性
 */
void MainWindow::setControlButtonVisibility()
{

    // 除“休息”按钮外全部隐藏，再根据状态显示
    ui->pushButton_start->hide();
    ui->pushButton_restart->hide();
    
    ui->pushButton_pause->hide();
    ui->pushButton_stop->hide();
    ui->pushButton_continue->hide();

    ui->pushButton_break->show();
    
    switch(tickState){
        case TickState::Count:
            ui->pushButton_restart->show();
            ui->pushButton_pause->show();
            ui->pushButton_stop->show();
            break;
        case TickState::Break:
            ui->pushButton_restart->show();
            break;
        case TickState::Overtime:
            ui->pushButton_restart->show();
            break;
        case TickState::Pause:
            ui->pushButton_restart->show();
            ui->pushButton_continue->show();
            ui->pushButton_stop->show();
            break;
        case TickState::Stop:
            ui->pushButton_restart->show();
            break;
        case TickState::Init:
        default:
            ui->pushButton_start->show();
            break;
    }
}

/**
 * 收集时间信息
 */
void MainWindow::collectTimeInfo()
{
    row["time"] = ui->lineEdit_time->text();
    row["tipTime"] = ui->lineEdit_tipTime->text();
    row["breakTime"] = ui->lineEdit_breakTime->text();
}


/**
 * 设置任务栏图标上的覆盖图标（固定大小16*16）
 * @param min
 */
void MainWindow::setOverlayIcon(short min)
{
    //qDebug() << "overlay min:" << min;
    if(min == lastOverlayMin){
        return;
    }
    lastOverlayMin = min;


    QPixmap icon(16, 16);
    icon.fill(Qt::transparent);

    QPainter painter(&icon);

    QFont font("Times", 10, QFont::ExtraBold);
    painter.setFont(font);

    painter.setPen(Qt::white);
    //painter.setPen(Qt::green);

    //QString text(min);
    QString text = QString("%1").arg(min);
    QRect rect(0, 0, 16, 16);
    painter.drawText(rect, Qt::AlignCenter, text);

    taskbarButton->setOverlayIcon(QIcon(icon));

}

/**
 * 设置任务栏图标进度条
 * @param state
 * @param value
 * @param maxValue
 */
void MainWindow::setTaskbarProgress(IconState state, qint64 value, qint64 maxValue)
{
    value = value >= Config::progressMinValue ? value : Config::progressMinValue;

    switch(state){
        case IconState::Normal:
            taskbarProgress->resume();
            break;
        case IconState::Pause:
            taskbarProgress->resume();
            taskbarProgress->pause();
            break;
        case IconState::Stop:
            taskbarProgress->stop();
            break;
        default:
            taskbarProgress->resume();
            break;
    }

    if(maxValue > 0){
        taskbarProgress->setMaximum(maxValue);
        taskbarProgress->setValue(value);
    }else{
        taskbarProgress->setRange(0, 0);
    }

}


void MainWindow::tickHook()
{
    checkAutoHide();
}

void MainWindow::checkAutoHide()
{
    if(newSetting["autoHide"].toBool()){
        QTimer::singleShot(newSetting["autoHideDelay"].toInt(), this, &MainWindow::setAutoHide);
    }
}

void MainWindow::setAutoHide()
{
    showMinimized();
}

void MainWindow::on_checkBox_countDown_released()
{
    
}

void MainWindow::on_checkBox_countDown_clicked(bool checked)
{
    newSetting["countDown"] = checked;
    tick();
}

void MainWindow::on_checkBox_autoHide_released()
{
    newSetting["autoHide"] = ui->checkBox_autoHide->isChecked();
}
