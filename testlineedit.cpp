#include "testlineedit.h"

TestLineEdit::TestLineEdit()
{
    
}

TestLineEdit::TestLineEdit(QWidget *parent)
    : QLineEdit(parent)
    //: QLineEdit(parent2)
    //: QWidget(parent)
    //: QWidget(parent)
{

}

void TestLineEdit::enterEvent(QEvent *event)
{
    this->selectAll();
    this->setFocus();
}

