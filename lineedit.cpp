#include "lineedit.h"
#include "ui_lineedit.h"

LineEdit::LineEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineEdit)
{
    ui->setupUi(this);
}

LineEdit::~LineEdit()
{
    delete ui;
}

void LineEdit::enterEvent(QEvent *event)
{
    ui->lineEdit->selectAll();
    ui->lineEdit->setFocus();
}
