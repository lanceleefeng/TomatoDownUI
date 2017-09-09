#ifndef TESTLINEEDIT_H
#define TESTLINEEDIT_H

#include <QLineEdit>

class TestLineEdit : public QLineEdit
{
public:
    TestLineEdit();
    TestLineEdit(QWidget *parent = Q_NULLPTR);

protected:
    void enterEvent(QEvent *event);

};

#endif // TESTLINEEDIT_H
