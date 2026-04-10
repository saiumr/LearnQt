#include "buttondemo.h"

#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QToolButton>
#include <QCheckBox>

ButtonDemo::ButtonDemo(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("Button Demo");
    setFixedSize(400, 300);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // QPushButton
    QPushButton *pushBtn = new QPushButton("普通按钮", this);
    connect(pushBtn, &QPushButton::clicked, this, []() {
        qDebug() << "普通按钮被点击";
    });
    mainLayout->addWidget(pushBtn);

    // 可切换的QPushButton
    QPushButton *toggleBtn = new QPushButton("开关按钮（按下/弹起）", this);
    toggleBtn->setCheckable(true);  // 打开可设置开关才能点击检测，触发下面的信号
    connect(toggleBtn, &QPushButton::toggled, this, [](bool clicked) {
        qDebug() << "开关按钮状态：" << (clicked ? "按下" : "弹起");
    });
    mainLayout->addWidget(toggleBtn);

    // QToolButton
    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->setIcon(QIcon(":/lee_ico.ico"));
    //toolBtn->setText("工具按钮");
    toolBtn->setToolTip("工具按钮悬停提示");
    connect(toolBtn, &QToolButton::clicked, this, [](){
        qDebug() << "工具按钮被点击";
    });
    mainLayout->addWidget(toolBtn);

    // 单选按钮 QRadioButton
    QWidget *radioGroup = new QWidget(this);
    QHBoxLayout *radioLayout = new QHBoxLayout(radioGroup);
    // parent相同即在一个group
    QRadioButton *radioA = new QRadioButton("选项A", radioGroup);
    QRadioButton *radioB = new QRadioButton("选项B", radioGroup);
    radioA->setChecked(true);  // 默认A为选中状态
    radioLayout->addWidget(radioA);
    radioLayout->addWidget(radioB);
    radioLayout->addStretch();
    mainLayout->addWidget(new QLabel("单选按钮组："));
    mainLayout->addWidget(radioGroup);
    // 获取当前选中的值
    QPushButton *radioCheckBtn = new QPushButton("获取选中的选项", radioGroup);
    radioLayout->addWidget(radioCheckBtn);
    connect(radioCheckBtn, &QPushButton::clicked, this, [radioA, radioB]() {
        if (radioA->isChecked()) {
            qDebug() << "选中了A";
        } else if (radioB->isChecked()) {
            qDebug() << "选中了B";
        }
    });

    // QCheckBox
    QCheckBox *checkBox = new QCheckBox("我同意条款", this);
    connect(checkBox, &QCheckBox::checkStateChanged, this, [](int state) {
        if (state == Qt::Checked) {
            qDebug() << "已同意";
        } else if (state == Qt::Unchecked) {
            qDebug() << "取消同意";
        }
    });
    mainLayout->addWidget(checkBox);

    // 三态复选框
    QCheckBox *triCheckBox = new QCheckBox("三态（半选）", this);
    triCheckBox->setTristate(true);  // 打开三态复选
    triCheckBox->setCheckState(Qt::PartiallyChecked);  // 设置默认状态
    connect(triCheckBox, &QCheckBox::checkStateChanged, this, [](int state) {
        qDebug() << "三态复选状态值：" << state;
    });
    mainLayout->addWidget(triCheckBox);

    // 在窗口最下方加个垂直弹簧
    mainLayout->addStretch();
}
