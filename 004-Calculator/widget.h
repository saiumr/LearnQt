#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;

    // 计算器状态变量
    QString currentInput;       // 当前输入的数字（字符串形式）
    double previousValue;       // 上一个操作数
    QString currentOperator;    // 当前运算符
    bool resetNextInput;        // 是否需要重置输入（输入新数字）

    // 辅助函数
    double calculate(double left, double right, const QString &op);
    void updateDisplay();       // 刷新显示屏
    void resetAll();            // 完全重置状态

private slots:
    void onDigitClicked();      // 数字键（0-9, 00, .）
    void onOperatorClicked();   // 运算符键（+ - × ÷）
    void onEqualClicked();      // 等号 =
    void onClearClicked();      // 清空 C
    void onBackspaceClicked();  // 退格 ⌫
    void onPlusMinusClicked();  // 正负号 ±
    void onPercentClicked();    // 百分号 %
    void onMemoryClicked();     // 内存键（MC/MR/MS 合并处理）
};
#endif // WIDGET_H
