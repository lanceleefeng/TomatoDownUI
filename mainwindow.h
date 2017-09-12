#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "basedata.h"
#include "lineedit.h"
#include "tools.h"

#include <QMainWindow>
#include <QDesktopWidget>

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


    bool initiated = false;

    QVariantMap row;
    void collectTimeInfo();

    QString defaultTimerKey;
    QMap<QString, qint64> timeConsumed;

    QMap<QString, QTimer *> timer;
    void createTimer(QString timerKey);

    QMap<QString, QVariant> newSetting;
    QMap<QString, QVariant> oldSetting;

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

public slots:

    void tick();

    void on_pushButton_start_released();

private slots:

    // 也可以不用自动生成的slots，自定义slots名称，并在MainWindow::MainWindow中手动connect

    void on_pushButton_restart_released();
    
    void on_pushButton_break_released();
    
    void on_pushButton_pause_released();
    
    void on_pushButton_stop_released();
    
    void on_pushButton_continue_released();



    void on_checkBox_countDown_released();
    
    void on_checkBox_countDown_clicked(bool checked);


    void on_checkBox_autoHide_released();

    void setAutoHide();

    
private:
    Ui::MainWindow *ui;


};

#endif // MAIN_WINDOW_H
