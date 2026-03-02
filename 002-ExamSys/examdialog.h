#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H

#include <QDialog>
#include <QTimer>
#include <memory>
#include <array>
#include <QTextEdit>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>

class ExamDialog : public QDialog
{
    Q_OBJECT
public:
    ExamDialog();
    void initTimer();     // 初始化计时器
    void initLayout();    // 初始化布局管理器
    bool initTextEdit();  // 初始化文本编辑器
    void initButtons();   // 初始化按钮及标签
private:
    std::unique_ptr<QTimer> m_timer; //计时器
    int m_timeGo;                    // 考试已用时

    std::unique_ptr<QTextEdit>                    m_textEdit;     // 考试题库显示
    std::array<std::unique_ptr<QLabel>, 10>       m_titleLabels;  // 题目标签
    std::array<std::unique_ptr<QRadioButton>, 32> m_radioBtns;    // 单选题按钮
    std::array<std::unique_ptr<QCheckBox>, 12>    m_checkBtns;    // 多选题按钮
    std::array<std::unique_ptr<QRadioButton>, 4>  m_radioA;       // 判断题A选项
    std::array<std::unique_ptr<QRadioButton>, 4>  m_radioB;       // 判断题B选项
    std::array<std::unique_ptr<QButtonGroup>, 7>  m_btnGroups; // 单选和判断按钮分组
    std::unique_ptr<QPushButton>                  m_submitBtn;    // 提交按钮
    std::unique_ptr<QGridLayout>                  m_layout;       // 布局管理器
    QStringList                                   answerList;

private slots:
    void freshTime();
};

#endif // EXAMDIALOG_H
