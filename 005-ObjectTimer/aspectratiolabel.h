#ifndef ASPECTRATIOLABEL_H
#define ASPECTRATIOLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class AspectRatioLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AspectRatioLabel(QWidget *parent = nullptr) : QLabel(parent) {}

    // 重写设置图片的函数，保存原图
    void setPixmap(const QPixmap &p) {
        originalPixmap = p;
        updatePixmap();
    }
    QSize minimumSizeHint() const override
    {
        // 返回一个很小的尺寸，允许窗口缩到任意大小
        return QSize(10, 10); // 或者 QSize(0, 0)
    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        QLabel::resizeEvent(event);
        updatePixmap(); // 窗口改变时自动重绘
    }

private:
    QPixmap originalPixmap;
    void updatePixmap() {
        if (originalPixmap.isNull()) return;
        // 保持宽高比，完整显示在 label 区域内（留白）
        QPixmap scaled = originalPixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QLabel::setPixmap(scaled);
    }
};

#endif // ASPECTRATIOLABEL_H