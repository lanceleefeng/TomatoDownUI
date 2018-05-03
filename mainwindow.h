#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "basedata.h"
#include "lineedit.h"
#include "tools.h"
#include "settingmodel.h"


#include <QtGui>
#include <QTranslator>

#include <QApplication>


#include <QMainWindow>
#include <QDesktopWidget>
#include <QCheckBox>

#include <QTimer>

#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QRect>


#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);
    //bool eventFilter(QObject *obj, QEvent *event);

    bool initiated = false;

    QVariantMap row;
    void collectTimeInfo();

    QString defaultTimerKey;
    QMap<QString, qint64> timeConsumed;

    QMap<QString, QTimer *> timer;
    void createTimer(QString timerKey);

    QMap<QString, bool> delayedActions;
    QString keySaveSetting = "saveSetting";

    //新旧设置分别改为SettingModel::setting、SettingModel::oldSetting
    //QMap<QString, QVariant> newSetting;
    //QMap<QString, QVariant> oldSetting;

    void beginSaveSetting();


    IconState iconState;
    TickState tickState;

    void setTickState(TickState state);
    void setControlButtonVisibility();

    short lastOverlayMin;

    QWinTaskbarButton *taskbarButton;
    QWinTaskbarProgress *taskbarProgress;

    void setOverlayIcon(short min);
    void setTaskbarProgress(IconState state, qint64 value, qint64 maxValue);

    void tickHook();
    void checkAutoHide();
    void setEndAtText(QDateTime time);

    QString language;
    //QApplication app;
    //QApplication *app;
    //QTranslator *translator;

    void switchLanguage();
    void refreshUi();

protected:

public slots:

    void tick();

    void on_pushButton_start_released();

    //void on_lineEdit_time_returnPressed();
    void on_lineEdit_tipTime_returnPressed();
    void on_lineEdit_breakTime_returnPressed();

private slots:

    // 也可以不用自动生成的slots，自定义slots名称，并在MainWindow::MainWindow中手动connect


    void on_pushButton_restart_released();
    
    void on_pushButton_break_released();
    
    void on_pushButton_pause_released();
    
    void on_pushButton_stop_released();
    
    void on_pushButton_continue_released();

    void on_checkBox_autoStart_clicked(bool checked);
    void on_checkBox_countDown_clicked(bool checked);
    void on_checkBox_autoHide_clicked(bool checked);

    void on_comboBox_language_activated(int index);
    //void on_comboBox_language_currentIndexChanged(int index);

    void setAutoHide();

    void endSaveSetting();


    
    
    
private:
    Ui::MainWindow *ui;


};

#endif // MAIN_WINDOW_H
