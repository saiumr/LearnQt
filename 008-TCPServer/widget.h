#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <memory>

#define PORT 9527

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void newClientHandler();
    // void clientInfoSlot();
    void threadSlot(QByteArray ba);

private:
    Ui::Widget *ui;
    std::unique_ptr<QTcpServer> server;
};
#endif // WIDGET_H
