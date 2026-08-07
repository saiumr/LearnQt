#include "widget.h"
#include "ui_widget.h"

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
    std::unique_ptr<QTcpSocket> socket { server->nextPendingConnection() };
    QString clnt_addr { socket->peerAddress().toString() };   // 获取客户端地址
    QString clnt_port { QString::number(socket->peerPort()) };      // 获取客户端端口号

    ui->lineEdit_clnt_addr->setText(clnt_addr);
    ui->lineEdit_clnt_port->setText(clnt_port);
}
