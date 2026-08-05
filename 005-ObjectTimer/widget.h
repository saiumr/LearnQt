#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#define TIMEOUT     1 * 1000    // ms


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
    void timerEvent(QTimerEvent* event) override;
    ~Widget() override;

private slots:
    void on_start_btn_clicked();

    void on_stop_btn_clicked();

private:
    Ui::Widget *ui;
    int my_object_timer_id;
    int picID;
};
#endif // WIDGET_H
