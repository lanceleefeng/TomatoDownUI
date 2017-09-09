#ifndef TESTPROMOTE_H
#define TESTPROMOTE_H

#include <QWidget>

namespace Ui {
class TestPromote;
}

class TestPromote : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestPromote(QWidget *parent = 0);
    ~TestPromote();

protected:
    void enterEvent(QEvent *event);

private:
    Ui::TestPromote *ui;
};

#endif // TESTPROMOTE_H
