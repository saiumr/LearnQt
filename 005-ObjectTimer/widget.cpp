#include "widget.h"
#include "ui_widget.h"
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("图片轮询查看");

    picID = 0;

    qDebug() << "pic cave0.jpg exist: " << QFile::exists(":/cave0.jpg");
    QPixmap pic(":/cave0.jpg");
    if (pic.isNull()) {
        qDebug() << "pic load failed!";
    } else {
        qDebug() << "pic loaded! size: " << pic.size();
    }
    ui->label->setPixmap(pic);
}

void Widget::timerEvent(QTimerEvent *event)
{
    // 识别定时器
    if (event->timerId() != my_object_timer_id)
        return;


    QString path {":/cave"};
    path += QString::number(picID);

    switch (picID) {
    case 1:
    case 2:
        path += ".png";
        break;
    default:
        path += ".jpg";
        break;
    }

    QPixmap pic(path);
    ui->label->setPixmap(pic);

    picID++;
    if (picID == 5) picID = 0;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_start_btn_clicked()
{

    qDebug() << "start button clicked";
    // 开启定时器，返回定时器编号
    my_object_timer_id = this->startTimer(TIMEOUT);
}

void Widget::on_stop_btn_clicked()
{
    this->killTimer(my_object_timer_id);
}

