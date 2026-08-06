#include "AspectRatioLabel.h"

AspectRatioLabel::AspectRatioLabel(QWidget *parent)
    : QLabel(parent)
{
    // 必须关闭，由我们自己实现缩放
    setScaledContents(false);
    // label内部图片居中
    setAlignment(Qt::AlignCenter);

    timer_interval = TIMEOUT_1_MS * 16;
    timer = std::make_unique<QTimer>();
    timer->setInterval(timer_interval);
    timer->setSingleShot(true);  // 单次触发
    connect(timer.get(), &QTimer::timeout, this, &AspectRatioLabel::updateScaledPixmap);
}

void AspectRatioLabel::setOriginalPixmap(const QPixmap &p)
{
    m_originalPix = p;
    updateScaledPixmap();
}

QPixmap AspectRatioLabel::originalPixmap() const
{
    return m_originalPix;
}

QSize AspectRatioLabel::minimumSizeHint() const
{
    // 切断原图对窗口最小尺寸约束，允许缩很小
    return QSize(40, 30);
}

QSize AspectRatioLabel::sizeHint() const
{
    if(m_originalPix.isNull())
        return QLabel::sizeHint();
    // hint不要返回原图大小，避免布局优先按原图分配空间
    return QSize(200,150);
}

void AspectRatioLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    timer->start(); // 缩放窗口时触发延迟更新，不立即更新图片
}

void AspectRatioLabel::updateScaledPixmap()
{
    if(m_originalPix.isNull())
    {
        QLabel::setPixmap(QPixmap());
        return;
    }

    //  Qt::KeepAspectRatio 保持图片原比例，把size()参数当成最大边框
    QPixmap scaled = m_originalPix.scaled(
        this->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );
    QLabel::setPixmap(scaled);
}
