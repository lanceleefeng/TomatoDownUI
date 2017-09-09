#include "testpromote.h"
#include "ui_testpromote.h"

TestPromote::TestPromote(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPromote)
{
    ui->setupUi(this);
}

TestPromote::~TestPromote()
{
    delete ui;
}

void TestPromote::enterEvent(QEvent *event)
{
    ui->lineEdit->selectAll();
    ui->lineEdit->setFocus();
}
