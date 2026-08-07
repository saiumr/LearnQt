#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <memory>

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
    void on_cancel_btn_clicked();
    void on_connect_btn_clicked();

private:
    Ui::Widget *ui;
    std::unique_ptr<QTcpSocket> socket;
};
#endif // WIDGET_H
