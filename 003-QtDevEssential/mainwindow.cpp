#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建中央控件和布局
    QWidget *central { new QWidget {this} };
    setCentralWidget(central);
    QVBoxLayout *layout { new QVBoxLayout {central} };

    // 创建图形控件和滑块
    m_circle = new ColorCircle { this };
    m_slider = new QSlider { Qt::Horizontal, this };
    m_slider->setRange(0, 360);    // 色相范围0-360

    // 创建按钮和标签
    m_btnShowColor = new QPushButton("读取圆形颜色", this);
    m_lblColorInfo = new QLabel("当前颜色：未读取", this);

    // 把组件通通添加到布局中
    layout->addWidget(m_circle, 0, Qt::AlignCenter);
    layout->addWidget(m_slider);
    layout->addWidget(m_btnShowColor);
    layout->addWidget(m_lblColorInfo);

    // 信号槽连接：滑块值变化 -> 改变图形的颜色
    connect(m_slider, &QSlider::valueChanged, this, [this](int hue) {
        QColor color;
        color.setHsv(hue, 255, 255);  // 饱和度、亮度固定
        // 传统方式设置 m_color
        // m_circle->setColor(color);
        // 动态属性方式：通过属性名设置
        m_circle->setProperty("color", color);
    });

    // [这个实际上没用到]：当圆形的颜色改变时，更新滑块的位置（实现双向同步）
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

    setWindowTitle("Qt Dev Essential");
    resize(600, 400);

    // 修改窗体风格：无边框、半透明
    // setWindowFlags(Qt::FramelessWindowHint);
    // setWindowOpacity(0.5);

    // 设置全局样式表
    setStyleSheet("QWidget { background-color: #1f1f1f; }"
                  "QPushButton { background-color: #2ecc71; color: white; border-radius: 5px; padding: 6px; }"
                  "QPushButton:hover { background-color: #27ae60; }"
                  "QLabel { color: #ff8080; font: 10pt; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}
