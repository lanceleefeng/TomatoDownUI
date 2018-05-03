#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
//Q_OBJECT

public:
    LineEdit();
    LineEdit(QWidget *parent = Q_NULLPTR);

protected:
    void enterEvent(QEvent *event);

};

#endif // LINE_EDIT_H
