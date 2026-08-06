#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , qrc_img_id(0)
{
    ui->setupUi(this);

    setWindowTitle("QTimer图片轮询查看");

    timer = std::make_unique<QTimer>();
    timer->setInterval(TIMEOUT_1_SEC);
    connect(timer.get(), &QTimer::timeout, this, &Widget::onTimerTimeout);

    image_path_list = std::move(getImageList(ASSETS_IMAGE_ROOT_DIR));

    if (!image_path_list.isEmpty()) {
        QImage image;
        image.load(image_path_list[0]);
        ui->label->setOriginalPixmap(QPixmap::fromImage(image));
    }
}

Widget::~Widget()
{
    delete ui;
}

QStringList Widget::getImageList(const QString &qrcDir)
{
    QStringList res;

    QDir dir { qrcDir };
    if (dir.isEmpty()) {
        QMessageBox::information(this, "糟糕", "资源路径\"" + qrcDir + "\"找不到");
    }

    // 选取图片文件
    // 跳过 . ..
    const auto entries = dir.entryList(
        QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp",
        QDir::Files | QDir::NoDotAndDotDot
    );
    for(const auto& name : entries)
    {
        // filePath自动拼接，得到完整资源路径 ":/images/xxx.png"
        // qDebug() << name;
        QString fullPath = dir.filePath(name);
        res.append(fullPath);
        // qDebug() << fullPath;
    }

    return res;
}

void Widget::on_btn_start_clicked()
{
    timer->start();
}

void Widget::on_btn_stop_clicked()
{
    timer->stop();
}

void Widget::onTimerTimeout()
{
    if (!image_path_list.isEmpty()) {
        if (qrc_img_id == image_path_list.size()) qrc_img_id = 0;
        ui->label->setOriginalPixmap(QPixmap {image_path_list[qrc_img_id++]} );
    } else {
        timer->stop();
        QMessageBox::warning(this, "错了错了", "图库里没有一张图");
    }
}

