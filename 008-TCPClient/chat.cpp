#include "chat.h"
#include "ui_chat.h"
#include <QMessageBox>

Chat::Chat(QTcpSocket* s, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chat)
    , socket(s)
{
    ui->setupUi(this);
    if (socket) {
        socket->setParent(this);
        connect(socket, &QTcpSocket::disconnected, this, [this]() {
            QMessageBox::information(this, "提示", "网络已断开");
        });
    }
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_clear_btn_clicked()
{
    ui->lineEdit->clear();
}


void Chat::on_send_btn_clicked()
{
    QByteArray ba;
    ba.append(ui->lineEdit->text().toUtf8());
    socket->write(ba);
}

