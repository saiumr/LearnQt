#include "examdialog.h"

ExamDialog::ExamDialog() {
    setWindowTitle("考试已用时：0分0秒");  // 开始时标题设置
    initTimer();
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

void ExamDialog::freshTime()
{
    m_timeGo++;
    QString sec { QString::number(m_timeGo % 60) }; // 秒
    QString min { QString::number(m_timeGo / 60) }; // 分
    setWindowTitle("考试已用时：" + min + "分" + sec + "秒");
}
