#include "examdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QRegularExpression>


ExamDialog::ExamDialog() {
    // 设置字体大小
    QFont font;
    font.setPointSize(12);
    setFont(font);
    // 设置窗口背景颜色
    setPalette(QPalette { QColor { 209, 215, 255 } });

    setWindowTitle("考试已用时：0分0秒");  // 开始时标题设置
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);  // 窗口只需要一个对话框和一个x关闭按钮，虽然Qt6不设置也对
    // 设置窗体大小
    resize(800, 600);
    initTimer();
    initLayout();
    if (!initTextEdit()) {
        QMessageBox::information(this, "提示", "初始化题库数据失败");
        // 立即响应退出函数，qApp是当前应用的全局对象，需要QApplication头文件
        // Qt6不再推荐SLOT SIGNAL
        // 可以用lambda直接调用
        // QTimer::singleShot(0, qApp, [](){
        //     qApp->quit();
        // });
        // Qt6新语法直接传函数指针
        QTimer::singleShot(0, qApp, &QApplication::quit);
    }
}

void ExamDialog::initTimer()
{
    m_timeGo = 0;
    m_timer = std::make_unique<QTimer>();
    m_timer->setInterval(1000);  // 设置触发间隔时间 1000ms
    m_timer->start();  // 启动计时器
    // 使用信号槽机制，在计时器触发时刷新时间显示
    // 连接信号槽，参数非常直观：发送者  信号  接受者  槽（一个函数）
    // Qt6新语法，直接把成员函数指针传递进去连接，不再使用古老的信号槽写法，connect是QObject的静态函数，直接写会报错
    QObject::connect(m_timer.get(), &QTimer::timeout, this, &ExamDialog::freshTime);
}

void ExamDialog::initLayout()
{
    m_layout = std::make_unique<QGridLayout>(this);
    // 设置控件间的间距
    m_layout->setSpacing(10);
    // 设置窗体和控件之间的间隔
    m_layout->setContentsMargins(10, 10, 10, 10);
}

bool ExamDialog::initTextEdit()
{
    // 读取整个题库放到文本编辑器中
    QString     strLine;
    QStringList strList;
    QString     filename { "../../exam.txt" };
    QFile       file { filename };
    QTextStream stream { &file };

    // 指定文件流编码，虽然我的没啥问题，可能是Qt6做了优化
    stream.setEncoding(QStringConverter::Utf8);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_textEdit = std::make_unique<QTextEdit>(this);
        QString strText;  // 保存所有题目，显示到文本编辑器
        int nLines {0};
        while (!stream.atEnd()) {
            strLine = stream.readLine();

            // 过滤掉答案行
            // 答案行是"答案："开头的，后面跟着一个或者多个大写字母，严格匹配
            QRegularExpression answer_regex { R"(^答案：[A-Z]+$)" };
            QRegularExpressionMatch match { answer_regex.match(strLine) };
            if (match.hasMatch()) {
                strList = strLine.split("：");
                answerList.append(strList.at(1));
                strText += '\n';  // 添加空行
                nLines++;
                continue;
            }

            strText += strLine;
            strText += '\n';
            nLines++;
        }
        // 文本编辑器设置文本内容
        m_textEdit->setText(strText);
        // 设置交互，只能查看或者选中复制，不能编辑(用setReadOnly)
        // m_textEdit->setTextInteractionFlags(Qt::TextBrowserInteraction);
        m_textEdit->setReadOnly(true);
        // 用表格的形式划分窗口布局，文本编辑器占据了一行十列，等会儿可以设置十个选项分别在每一列
        m_layout->addWidget(m_textEdit.get(), 0, 0, 1, 10);
        return true;
    } else {
        return false;
    }
}

void ExamDialog::freshTime()
{
    m_timeGo++;
    QString sec { QString::number(m_timeGo % 60) }; // 秒
    QString min { QString::number(m_timeGo / 60) }; // 分
    setWindowTitle("考试已用时：" + min + "分" + sec + "秒");
}
