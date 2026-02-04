#include "logindialog.h"
#include "./ui_logindialog.h"
#include <QMessageBox>
#include <QRegularExpression>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    // label图片填充
    ui->label_bg->setScaledContents(true);
    // 窗口设置成背景图label大小
    this->resize(ui->label_bg->width(), ui->label_bg->height());
    // 设置窗体风格
    this->setWindowTitle("驾校科目一考试登录");
    // For Dialog windows, the Close button is enabled by default.
    // this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setWindowFlags(Qt::Dialog);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_button_login_clicked()
{
    // 利用提示框可以插桩调试
    // QMessageBox::information(this, "提示", "槽方法调用");

    // 正则验证邮箱地址：用户名@域名  99love@qq.com
    // 元字符解释：^表示规则字符串的开始  $表示规则字符串的结束
    // +表示匹配次数>=1次  *表示可以匹配任意次数(可以是0次)  {n,m}匹配此时[n,m]
    // 用^...$锚定整个字符串会进行精确匹配
    QRegularExpression rx { "^[A-Za-z0-9]+([_\.][A-Za-z0-9]+)*@([A-Za-z0-9-]+\.)+[A-Za-z]{2,6}$" };
    QRegularExpressionMatch match { rx.match(ui->lineEdit_account->text()) };

    if (!match.hasMatch()) {
        QMessageBox::information(this, "提示", "非法的邮箱地址，请你重新输入！");
    } else {
        QMessageBox::information(this, "提示", "欢迎登录科目一考试系统！");
    }

}

