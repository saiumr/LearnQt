#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QImage image;
    image.load(":/images/cave0.jpg");
    ui->label->setOriginalPixmap(QPixmap::fromImage(image));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_start_clicked()
{

}


void Widget::on_pushButton_2_clicked()
{

}

