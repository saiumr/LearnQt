#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialog>
#include "dynamicpropertydemo.h"
#include "colorinputdialog.h"

DynamicPropertyDemo::DynamicPropertyDemo(QWidget* parent) : QWidget(parent) {
    // 设置独立窗口标题
    setWindowTitle("动态属性和对话框");

    // 创建中央控件和布局
    QVBoxLayout *layout { new QVBoxLayout {this} };

    // 创建图形控件和滑块
    m_circle = new ColorCircle { this };
    m_slider = new QSlider { Qt::Horizontal, this };
    m_slider->setRange(0, 360);    // 色相范围0-360

    // 创建按钮和标签
    m_btnShowColor = new QPushButton("读取圆形颜色", this);
    m_lblColorInfo = new QLabel("当前颜色：未读取", this);

    // 让圆形区域占据大部分空间，滑块和按钮固定高度
    m_circle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 圆形可扩展
    m_slider->setFixedHeight(30);        // 滑块固定高度
    m_btnShowColor->setFixedSize(100, 30);
    m_lblColorInfo->setFixedHeight(25);

    // 把组件通通添加到布局中
    // layout->addWidget(m_circle, 1, Qt::AlignCenter);  // 有Alignment也不会自动拉伸了
    layout->addWidget(m_circle, 1);         // 占据1份空间（其他的为0，就是说缩放窗口时多余空间全都分配给圆形）
    layout->addWidget(m_slider, 0);         // 0 表示不拉伸，按固定高度
    layout->addWidget(m_btnShowColor, 0);
    layout->addWidget(m_lblColorInfo, 0);
    layout->addStretch();  // 底部添加弹性空间，让上面控件靠上紧密排列

    // 信号槽连接：滑块值变化 -> 改变图形的颜色
    connect(m_slider, &QSlider::valueChanged, this, [this](int hue) {
        QColor color;
        color.setHsv(hue, 255, 255);  // 饱和度、亮度固定
        // 传统方式设置 m_color
        // m_circle->setColor(color);
        // 动态属性方式：通过属性名设置
        m_circle->setProperty("color", color);
    });

    // 当圆形的颜色改变时，更新滑块的位置（实现双向同步）
    connect(m_circle, &ColorCircle::colorChanged, this, [this](const QColor &color) {
        int hue { color.hue() };
        if (hue == -1) hue = 0;        // 无色调（如黑色）时归零
        m_slider->blockSignals(true);  // 防止循环触发
        m_slider->setValue(hue);
        m_slider->blockSignals(false);
    });

    // 点击按钮时，读取圆形颜色并显示
    connect(m_btnShowColor, &QPushButton::clicked, this, [this]() {
        // 动态属性读
        QColor color = m_circle->property("color").value<QColor>();
        QString str = QString("当前颜色：RGB(%1, %2, %3)")
                          .arg(color.red()).arg(color.green()).arg(color.blue());
        m_lblColorInfo->setText(str);
    });

    resize(600, 700);               // 初始大小
    setMinimumSize(300, 300);       // 最小限制

    // 修改窗体风格：无边框、半透明
    // setWindowFlags(Qt::FramelessWindowHint);
    // setWindowOpacity(0.5);

    // 设置全局样式表
    setStyleSheet("QWidget { background-color: #1f1f1f; }"
                  "QPushButton { background-color: #2ecc71; color: white; border-radius: 5px; padding: 6px; }"
                  "QPushButton:hover { background-color: #27ae60; }"
                  "QLabel { color: #ff8080; font: 10pt; }");

    // 添加唤起颜色输入框的按钮
    QPushButton *btnColorDialog = new QPushButton("自定义颜色", this);
    layout->addWidget(btnColorDialog);
    connect(btnColorDialog, &QPushButton::clicked, this, &DynamicPropertyDemo::onColorInput);

}

void DynamicPropertyDemo::onColorInput()
{
    ColorInputDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        // 到此处已经调用了 accept
        QColor color = dlg.getColor();
        if (color.isValid()) {
            m_circle->setColor(color);  // 设置颜色，发射信号，同步滑块位置
        } else {
            QMessageBox::warning(this, "无效颜色", "输入颜色无效，请重新输入");
        }
    } else {
        // 到此处已经调用了 reject
    }
}
