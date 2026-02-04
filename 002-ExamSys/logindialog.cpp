#include "logindialog.h"
#include "./ui_logindialog.h"

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
