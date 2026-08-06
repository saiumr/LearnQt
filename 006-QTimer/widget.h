#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <memory>
#include <QStringList>
#include "common.h"

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
    void on_btn_start_clicked();
    void on_btn_stop_clicked();
    void onTimerTimeout();

private:
    Ui::Widget *ui;
    std::unique_ptr<QTimer> timer;
    QStringList image_path_list;
    QStringList getImageList(const QString& qrcDir);
    int qrc_img_id;
};
#endif // WIDGET_H
