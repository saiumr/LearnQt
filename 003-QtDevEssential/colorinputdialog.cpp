#include "colorinputdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QColor>

ColorInputDialog::ColorInputDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("输入颜色");
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("请输入颜色名或十六"
                                 "进制（如 red, #ff0000）:"));
    m_lineEdit = new QLineEdit(this);
    layout->addWidget(m_lineEdit);

    QPushButton *okBtn = new QPushButton("确定", this);
    QPushButton *cancelBtn = new QPushButton("取消", this);
    layout->addWidget(okBtn);
    layout->addWidget(cancelBtn);

    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

QColor ColorInputDialog::getColor() const
{
    return QColor(m_lineEdit->text());
}


