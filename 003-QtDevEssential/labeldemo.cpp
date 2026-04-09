#include "labeldemo.h"
#include <QVBoxLayout>
#include <QLabel>

LabelDemo::LabelDemo(QWidget *parent) : QWidget(parent) {
    setWindowTitle("QLabel Demo");
    setMinimumSize(400, 300);
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 普通文本
    QLabel *textLabel = new QLabel("普通文本标签", this);
    layout->addWidget(textLabel);

    // 对齐方式
    QLabel *alignLabel = new QLabel("居中对齐", this);
    alignLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(alignLabel);

    // 数字显示
    QLabel *numLabel = new QLabel(QString("当前数值：%1").arg(42), this);
    layout->addWidget(numLabel);

    // 图片显示
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":/images/logo.png");
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap);
        imageLabel->setScaledContents(true);
        imageLabel->setFixedSize(100, 100);
    } else {
        imageLabel->setText("图片未找到");
    }
    layout->addWidget(imageLabel);

    // 富文本
    QLabel *htmlLabel = new QLabel("<b>粗体</b> 和 <i>斜体</i> 以及 <font color=red>红色</font>", this);
    layout->addWidget(htmlLabel);

    // 超链接
    QLabel *linkLabel = new QLabel("<a href='https://tieba.baidu.com/index.html'>百度贴吧</a>", this);
    linkLabel->setOpenExternalLinks(true);
    layout->addWidget(linkLabel);
}

LabelDemo::~LabelDemo()
{
    qDebug() << "Label演示窗口释放了";
}
