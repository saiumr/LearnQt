#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("TCP客户端");

    socket = std::make_unique<QTcpSocket>();

    // 判断连接成功：socket对象会发出信号
    connect(socket.get(), &QTcpSocket::connected, this, [this]()
    {
        QMessageBox::information(this, "连接提示", "连接成功");
    });

    // 连接断开：socket对象会发出信号
    connect(socket.get(), &QTcpSocket::disconnected, this, [this]()
    {
        QMessageBox::information(this, "连接提示", "连接异常 网络断开");
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_cancel_btn_clicked()
{
    this->close();
}


void Widget::on_connect_btn_clicked()
{
    QString ip_addr = ui->lineEdit_addr->text().trimmed();
    QString portStr = ui->lineEdit_port->text().trimmed();

    qDebug() << "ip:" << ip_addr << "portStr:" << portStr;

    bool ok;
    quint16 port = static_cast<quint16>(portStr.toUInt(&ok));
    if(!ok || port == 0)
    {
        QMessageBox::warning(this, "参数错误", "端口号非法");
        return;
    }

    QHostAddress addr(ip_addr);
    if(addr.isNull())
    {
        QMessageBox::warning(this, "参数错误", "IP地址格式错误");
        return;
    }

    // 如果socket现在正在连接/已连接，先断开旧连接（不是未连接状态就断开）
    if(socket->state() != QTcpSocket::UnconnectedState)
    {
        socket->disconnectFromHost();
    }

    // 仅仅发起连接，异步，函数马上返回，不阻塞UI
    socket->connectToHost(addr, port);
}

