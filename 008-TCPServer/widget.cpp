#include "widget.h"
#include "ui_widget.h"
#include "mythread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    server = std::make_unique<QTcpServer>();

    // 与原生api开发对比，不用手动去bind
    server->listen(QHostAddress::AnyIPv4, PORT);

    // 客户端发起连接，server发出信号
    connect(server.get(), &QTcpServer::newConnection, this, &Widget::newClientHandler);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::newClientHandler()
{
    // 建立TCP连接（注意这里unique指针，是直接通过裸指针构造的）
    QTcpSocket* socket { server->nextPendingConnection() };
    socket->setParent(this);
    QString clnt_addr { socket->peerAddress().toString() };   // 获取客户端地址
    QString clnt_port { QString::number(socket->peerPort()) };      // 获取客户端端口号

    ui->lineEdit_clnt_addr->setText(clnt_addr);
    ui->lineEdit_clnt_port->setText(clnt_port);

    // 收到客户端发出的消息，socket发出ReadyRead信号
    // connect(socket, &QTcpSocket::readyRead, this, &Widget::clientInfoSlot);

    // 启动线程 - 继承Qt的线程类
    MyThread* t { new MyThread(socket) };
    t->start();   // 开始线程

    // 连接自定义信号
    connect(t, &MyThread::sendToWidget, this, &Widget::threadSlot);
}

void Widget::threadSlot(QByteArray ba)
{
    ui->mainLineEdit->setText(ba);
}

// void Widget::clientInfoSlot()
// {
//     // 获取信号的发出者
//     QTcpSocket* s { (QTcpSocket*)sender() };
//     ui->mainLineEdit->setText(QString(s->readAll()));
// }
