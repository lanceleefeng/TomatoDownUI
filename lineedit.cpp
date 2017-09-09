#include "lineedit.h"

LineEdit::LineEdit()
{
    
}

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
    //: QLineEdit(parent2)
    //: QWidget(parent)
    //: QWidget(parent)
{

}

void LineEdit::enterEvent(QEvent *event)
{
    this->selectAll();
    this->setFocus();
}

