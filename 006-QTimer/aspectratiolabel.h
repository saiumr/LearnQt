#ifndef ASPECTRATIOLABEL_H
#define ASPECTRATIOLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>
#include <QTimer>
#include <memory>

class AspectRatioLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AspectRatioLabel(QWidget *parent = nullptr);

    // 派生类接口
    void setOriginalPixmap(const QPixmap &p);
    QPixmap originalPixmap() const;

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap m_originalPix;
    void updateScaledPixmap();
    std::unique_ptr<QTimer> timer;
    int timer_interval;
};

#endif // ASPECTRATIOLABEL_H