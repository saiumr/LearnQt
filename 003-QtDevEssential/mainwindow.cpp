#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynamicpropertydialog.h"
#include <QVBoxLayout>
#include <QMargins>
#include <QFontMetrics>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置控件容器避免控件重叠
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *layout = new QVBoxLayout(central);

    // new 按钮
    m_btnDynamic = new QPushButton(central);
    m_btnLabel = new QPushButton(central);

    // 添加按钮到布局
    addStyleButton(layout, m_btnDynamic, "动态属性和对话框");
    addStyleButton(layout, m_btnLabel, "Label演示");

    // 设置一点内外边距
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(2);
    // 加个垂直弹簧，把按钮顶到一起
    layout->addStretch();

    // 连接信号槽
    connect(m_btnDynamic, &QPushButton::clicked, this, &MainWindow::openDynamicProperDemo);
    connect(m_btnLabel, &QPushButton::clicked, this, &MainWindow::openLabelDemo);

    // 设定窗口属性
    setWindowTitle("Qt Dev Essential");
    resize(600, 450);
    setMinimumSize(400, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDynamicProperDemo()
{
    DynamicPropertyDialog *dlg = new DynamicPropertyDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::openLabelDemo()
{
    qDebug() << "打开QLabel功能演示";
}

void MainWindow::addStyleButton(QBoxLayout *layout, QPushButton *btn, const QString &text, int fixed_width)
{
    // 设置样式，文本默认是居中显示，改为左对齐，距上下边界1px，左右边界5px
    btn->setStyleSheet(R"(
        QPushButton {
            text-align: left;
            padding: 1px 5px;
        }
    )");

    // 溢出文字改为...显示
    QFontMetrics fm(btn->font());
    int textWidth = fixed_width - 10;  // 上面样式设置了左右5px的间距，这里减掉10可用宽度
    QString showText = fm.elidedText(text, Qt::ElideRight, textWidth);  // 自动生成带省略号的文本
    btn->setText(showText);

    // 鼠标悬停显示原文本
    btn->setToolTip(text);

    // 设置按钮固定宽度
    btn->setFixedWidth(fixed_width);

    // 按钮左对齐添加到布局中
    layout->addWidget(btn, 0, Qt::AlignLeft);
}

