#include "lineeditdemo.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QMessageBox>

LineEditDemo::LineEditDemo(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("LineEdit Demo");
    setFixedSize(400, 300);
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 基础输入框 + 清空按钮
    QLineEdit *basicEdit = new QLineEdit(this);
    basicEdit->setPlaceholderText("普通输入框（带清空按钮）");
    basicEdit->setClearButtonEnabled(true);
    layout->addWidget(basicEdit);

    // 密码框
    QLineEdit *pwdEdit = new QLineEdit(this);
    pwdEdit->setPlaceholderText("密码框");
    pwdEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(pwdEdit);

    // 数字范围限制
    QLineEdit *ageEdit = new QLineEdit(this);
    ageEdit->setPlaceholderText("年龄（0-120）");
    ageEdit->setValidator(new QIntValidator(0, 120, this));  // 只能阻止非法输入（非数字，三位数以上，字母符号等等），对于超过限制的数字认定为中间状态（Qt认为用户会再修改）
    // 提交验证
    QPushButton *checkAgeBtn = new QPushButton("提交年龄（验证器）", this);
    connect(checkAgeBtn, &QPushButton::clicked, this, [ageEdit, this]() {
        QString text = ageEdit->text();
        int pos = 0;
        QValidator::State state = ageEdit->validator()->validate(text, pos);

        if (state == QValidator::Acceptable) {
            QMessageBox::information(this, "成功", QString("年龄有效：%1 岁").arg(text));
        } else if (state == QValidator::Intermediate) {
            QMessageBox::warning(this, "输入不完整", "当前数字超出范围或未完成，请输入0-120之间的整数");
        } else { // Invalid
            QMessageBox::warning(this, "输入错误", "请输入0-120之间的整数（不能包含字母或符号）");
        }
    });
    layout->addWidget(ageEdit);
    layout->addWidget(checkAgeBtn);

    // 实时显示输入长度
    QLineEdit *countEdit = new QLineEdit(this);
    countEdit->setPlaceholderText("输入文字，下方显示长度");
    QLabel *lengthLabel = new QLabel("长度：0", this);
    connect(countEdit, &QLineEdit::textEdited, this, [lengthLabel](const QString& text) {
        lengthLabel->setText(QString("长度：%1").arg(text.length()));
    });
    layout->addWidget(countEdit);
    layout->addWidget(lengthLabel);

    // 回车提交
    QLineEdit *submitEdit = new QLineEdit(this);
    submitEdit->setPlaceholderText("输入内容后按回车");
    connect(submitEdit, &QLineEdit::returnPressed, this, [submitEdit]() {
        qDebug() << submitEdit->text();
    });
    layout->addWidget(submitEdit);


    layout->addStretch();
}
