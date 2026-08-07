#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentFilePath("")
    , m_WindowTitle(":D NotePad")
    , m_newFile(true)
{
    ui->setupUi(this);
    this->setWindowTitle(m_WindowTitle);

    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui->quickSaveAction, &QAction::triggered, this, &MainWindow::quickSaveActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newActionSlot()
{
    QString initDir { getInitDir(m_currentFilePath) };
    QString fileName { "新建文本文档.txt" };
    m_currentFilePath = initDir + "/" + fileName;

    this->setWindowTitle(m_WindowTitle + "（" + fileName + "）");
    m_newFile = true;
    ui->textEdit->clear();
}

void MainWindow::openActionSlot()
{
    // 初始目录：exe所在文件夹
    // QString dir = QCoreApplication::applicationDirPath();
    // 用户桌面目录
    QString dir { QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) };

    QString fileName {
        QFileDialog::getOpenFileName(
            this,
            tr("选择一个文件"),
            dir,
            tr("文本文件 (*.txt);;源文件 (*.c *.cpp *.h);;所有文件 (*)")
        )
    };

    // 用户点取消，直接return
    if (fileName.isEmpty())
        return;

    m_currentFilePath = fileName;
    this->setWindowTitle(m_WindowTitle + "（" + fileName + "）");
    // qDebug() << fileName;

    QFile file { fileName };
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, "凎", "超出能力范围，这个文件读不了");
        return;
    }

    QByteArray ba { file.readAll() };
    ui->textEdit->setText(QString(ba));

    file.close();
    m_newFile = false;
}

void MainWindow::quickSaveActionSlot()
{
    // 保存新文件，或者没有文件路径，就调用另存为
    if(m_newFile || m_currentFilePath.isEmpty())
    {
        saveActionSlot();
        return;
    }

    // 直接覆盖旧文件，不弹对话框
    QFile file(m_currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("保存失败"), file.errorString());
        return;
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    // qDebug() << "Save";
    file.close();
}

void MainWindow::saveActionSlot()
{
    QString initDir { getInitDir(m_currentFilePath) };

    QString fileName {
        QFileDialog::getSaveFileName(
            this,
            tr("另存为"),
            initDir,
            tr("文本文件 (*.txt);;源文件 (*.c *.cpp *.h);;所有文件 (*)")
        )
    };

    // 用户点取消，直接返回，什么都不做
    if (fileName.isEmpty())
        return;

    // 写入文本
    QFile file(fileName);
    // QIODevice::Text 文本模式，处理换行符
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("保存失败"), tr("无法写入文件：%1\n%2")
                    .arg(fileName, file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();

    file.close();

    if (m_newFile) {
        this->setWindowTitle(m_WindowTitle + "（" + fileName + "）");
        m_newFile = false;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    if (k->modifiers() == Qt::ControlModifier && k->key() == Qt::Key_S) {
        quickSaveActionSlot();
    }
}

QString MainWindow::getInitDir(QString filePath)
{
    // 根据文件路径获取起始目录（文件不存在就返回桌面目录）
    QString initDir;
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo { m_currentFilePath };
        initDir = fileInfo.absolutePath(); // 当前文件所在目录
    } else {
        initDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }

    return initDir;
}
