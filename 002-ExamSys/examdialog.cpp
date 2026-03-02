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
    // setPalette(QPalette { QColor { 209, 215, 255 } });
    // setPalette创建了一个只有一个颜色的“残缺调色板”，
    // 把系统样式绘制 QCheckBox √ 画成了和背景几乎一样的颜色导致看不到
    // 使用下面的设置仅改变窗口颜色
    this->setStyleSheet("QDialog { background-color: rgb(31,31,31); }");

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
    initButtons();
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

void ExamDialog::initButtons()
{
    QStringList strList { "A", "B", "C", "D" };
    int judgeIndex = 0;
    int singleCount = 0;
    int multiCount = 0;
    int btnGroupsCount = 0;
    bool add_single { false };
    // 总共10个题目  4判断，3多选，3单选
    for (int i = 0; i < 10; i++) {
        // 题目标签
        m_titleLabels[i] = std::make_unique<QLabel>(this);
        m_titleLabels[i]->setText("第" + QString::number(i+1) + "题");
        m_layout->addWidget(m_titleLabels[i].get(), 1, i);

        // 判断题
        switch (i) {
        case 0:
        case 3:
        case 6:
        case 9:
            m_radioA[judgeIndex] = std::make_unique<QRadioButton>(this);
            m_radioB[judgeIndex] = std::make_unique<QRadioButton>(this);
            m_radioA[judgeIndex]->setText("A.正确");
            m_radioB[judgeIndex]->setText("B.错误");
            m_layout->addWidget(m_radioA[judgeIndex].get(), 2, i);
            m_layout->addWidget(m_radioB[judgeIndex].get(), 3, i);

            m_btnGroups[btnGroupsCount] = std::make_unique<QButtonGroup>(this);
            m_btnGroups[btnGroupsCount]->addButton(m_radioA[judgeIndex].get());
            m_btnGroups[btnGroupsCount]->addButton(m_radioB[judgeIndex].get());
            judgeIndex++;
            btnGroupsCount++;

            continue;
            break;
        default:
            break;
        }

        // 选择题
        if (i == 2 || i == 5 || i == 8) {
            // 多选题
            for (int j = 0; j < 4; j++) {
                int index = 4 * multiCount + j;
                m_checkBtns[index] = std::make_unique<QCheckBox>(this);
                m_checkBtns[index]->setText(strList.at(j));
                m_layout->addWidget(m_checkBtns[index].get(), j+2, i);
            }
            multiCount++;
        } else {
            // 按钮分组
            m_btnGroups[btnGroupsCount] = std::make_unique<QButtonGroup>(this);
            // 单选题
            for (int j = 0; j < 4; j++) {
                int index = 4 * singleCount + j;
                m_radioBtns[index] = std::make_unique<QRadioButton>(this);
                m_radioBtns[index]->setText(strList[j]);
                m_layout->addWidget(m_radioBtns[index].get(), j+2, i);
                m_btnGroups[btnGroupsCount]->addButton(m_radioBtns[index].get());
            }
            singleCount++;
            btnGroupsCount++;
        }
    }

    // 提交解答的按钮
    m_submitBtn = std::make_unique<QPushButton>(this);
    m_submitBtn->setText("提交");
    m_submitBtn->setFixedSize(100, 35);
    m_layout->addWidget(m_submitBtn.get(), 6, 9);
}

void ExamDialog::freshTime()
{
    m_timeGo++;
    QString sec { QString::number(m_timeGo % 60) }; // 秒
    QString min { QString::number(m_timeGo / 60) }; // 分
    setWindowTitle("考试已用时：" + min + "分" + sec + "秒");
}
