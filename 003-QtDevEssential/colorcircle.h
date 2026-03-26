#ifndef COLORCIRCLE_H
#define COLORCIRCLE_H

#include <QWidget>
#include <QColor>
#include <QPaintEvent>

class ColorCircle : public QWidget
{
    Q_OBJECT
    // 暴露 color 属性：可读写，变化时发出 colorChanged 信号
    // FINAL表示这个 color 属性到此为止，任何子类都不允许再定义一个同名的 color 属性来覆盖它。
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
public:
    explicit ColorCircle(QWidget *parent = nullptr);

    QColor color() const { return m_color; }
    void   setColor(const QColor& newColor);

signals:
    void colorChanged(const QColor &newColor);  // 属性变化通知

protected:
    void paintEvent(QPaintEvent *event) override;  // 绘制圆形，QWidget中的虚函数

private:
    QColor m_color { Qt::red };
};

#endif // COLORCIRCLE_H
