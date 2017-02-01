#include "street.h"
#include "ui_street.h"

street::street(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::street)
{
    ui->setupUi(this);
}

street::~street()
{
    delete ui;
}
