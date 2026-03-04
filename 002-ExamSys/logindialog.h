#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginDialog;  // Ui_LoginDialog的子类，用于描述登录窗口界面信息
}
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT  // 继承自QObject类就有这个宏，支持信号槽机制

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_button_login_clicked();

    void on_button_cancel_clicked();

private:
    Ui::LoginDialog *ui;
};
#endif // LOGINDIALOG_H
