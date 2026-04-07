#include "colorcircle.h"
#include <QPainter>

ColorCircle::ColorCircle(QWidget *parent)
    : QWidget{parent}
{
    // setFixedSize(100, 100);  // 固定大小，好设计布局
    // 设置一个初始大小（可选，布局会参考 sizeHint）
    resize(50, 50);
}

void ColorCircle::setColor(const QColor &newColor)
{
    if (m_color == newColor) return;
    m_color = newColor;
    update();                       // 颜色改变触发重绘
    emit colorChanged(newColor);    // 发射信号
}

ColorCircle::~ColorCircle()
{
    qDebug() << "ColorCircle 被销毁了";
}

QSize ColorCircle::sizeHint() const
{
    return QSize(150, 150);  // 返回一个“建议大小”，初始布局会以此为基础进行伸缩
}

void ColorCircle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter { this };
    painter.setRenderHint(QPainter::Antialiasing, true);  // 抗锯齿
    painter.setBrush(m_color);
    painter.setPen(Qt::NoPen);        // 无边框
    painter.drawEllipse(rect());      // 填充整个区域

}
