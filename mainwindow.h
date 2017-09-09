#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "lineedit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    // 也可以不用自动生成的slots，自定义slots名称，并在MainWindow::MainWindow中手动connect
    void on_pushButton_hide_clicked();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
