#include "logindialog.h"
#include "./ui_logindialog.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QFile>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    // label图片填充
    ui->label_bg->setScaledContents(true);
    // 窗口设置成背景图label大小
    this->resize(ui->label_bg->width(), ui->label_bg->height());
    // 设置固定的窗口大小
    setFixedSize(width(), height());
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
    // 使用原生字符 R"()"，c++编译器不会转义'\'，从而被正则表达式使用
    QRegularExpression rx { R"(^[A-Za-z0-9]+([_\.][A-Za-z0-9]+)*@([A-Za-z0-9-]+\.)+[A-Za-z]{2,6}$)" };
    QRegularExpressionMatch match { rx.match(ui->lineEdit_account->text()) };

    if (!match.hasMatch()) {
        QMessageBox::information(this, "提示", "非法的邮箱地址，请你重新输入！");
        // 自动清理输入框（lineEdit），实际上不一定需要，用户可能只是输入错误了几个字符
        ui->lineEdit_account->clear();
        ui->lineEdit_passwd->clear();
        // 自动聚焦到输入框
        ui->lineEdit_account->setFocus();
        return;
    } else {
        // QMessageBox::information(this, "提示", "欢迎登录科目一考试系统！");
        QString filename;
        QString strAccount;     // 用户输入的账号
        QString strPasswd;      // 用户输入的密码
        QString strLine;        // 行读取
        QStringList strList;    // 字符串列表保存从文件读取到的账号和密码

        filename = "../../account.txt";
        strAccount = ui->lineEdit_account->text();
        strPasswd = ui->lineEdit_passwd->text();

        QFile file { filename };
        QTextStream stream { &file };

        // 只读打开纯文本
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while (!stream.atEnd()) {
                strLine = stream.readLine();
                strList = strLine.split(',');
                if (strAccount == strList.at(0)) {
                    if (strPasswd == strList.at(1)) {
                        QMessageBox::information(this, "提示", "欢迎登录科目一考试系统！");
                        file.close();
                        // todo: 此处登录成功，跳转到主界面
                        return;
                    } else {
                        QMessageBox::information(this, "提示", "密码错误，请重新输入！");
                        ui->lineEdit_passwd->clear();
                        ui->lineEdit_passwd->setFocus();
                        file.close();
                        return;
                    }
                }
            }

            // 遍历完了所有账号没找到
            // 提示完恢复数据状态
            QMessageBox::information(this, "提示", "账号错误，请重新输入！");
            ui->lineEdit_account->clear();
            ui->lineEdit_passwd->clear();
            ui->lineEdit_account->setFocus();
            file.close();
            return;

        } else {
            QMessageBox::information(this, "提示", "读取账号数据文件失败！");
            return;
        }
    }

}

