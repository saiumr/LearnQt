#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H

#include <QDialog>
#include <QTimer>
#include <memory>

class ExamDialog : public QDialog
{
    Q_OBJECT
public:
    ExamDialog();
    void initTimer();
private:
    std::unique_ptr<QTimer> m_timer; //计时器
    int m_timeGo;                    // 考试已用时
private slots:
    void freshTime();
};

#endif // EXAMDIALOG_H
