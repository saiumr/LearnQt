#include "widget.h"
#include "ui_widget.h"
#include <limits>
#include <QMessageBox>

constexpr double kEps = std::numeric_limits<double>::epsilon();

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , currentInput("0")          // 初始显示 0
    , previousValue(0.0f)
    , currentOperator("")
    , resetNextInput(false)
{
    ui->setupUi(this);

    // 连接所有按键信号和槽
    // 0-9 00 .
    connect(ui->btn0, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn1, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn2, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn3, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn4, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn5, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn6, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn7, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn8, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn9, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btn00, &QPushButton::clicked, this, &Widget::onDigitClicked);
    connect(ui->btnDot, &QPushButton::clicked, this, &Widget::onDigitClicked);

    // + - × ÷
    connect(ui->btnPlus, &QPushButton::clicked, this, &Widget::onOperatorClicked);
    connect(ui->btnMinus, &QPushButton::clicked, this, &Widget::onOperatorClicked);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &Widget::onOperatorClicked);
    connect(ui->btnDivide, &QPushButton::clicked, this, &Widget::onOperatorClicked);

    // = C ⌫ ± %
    connect(ui->btnEqual, &QPushButton::clicked, this, &Widget::onEqualClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &Widget::onClearClicked);
    connect(ui->btnBack, &QPushButton::clicked, this, &Widget::onBackspaceClicked);
    connect(ui->btnPlusMinus, &QPushButton::clicked, this, &Widget::onPlusMinusClicked);
    connect(ui->btnPercent, &QPushButton::clicked, this, &Widget::onPercentClicked);

    // MC MR MS
    connect(ui->btnMC, &QPushButton::clicked, this, &Widget::onMemoryClicked);
    connect(ui->btnMR, &QPushButton::clicked, this, &Widget::onMemoryClicked);
    connect(ui->btnMS, &QPushButton::clicked, this, &Widget::onMemoryClicked);

    updateDisplay();
}

Widget::~Widget()
{
    delete ui;
}

double Widget::calculate(double left, double right, const QString &op)
{
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "×") return left * right;
    if (op == "÷") {
        if (std::fabs(right) < kEps) {
            QMessageBox::warning(this, "警告", "发生除0错误！");
            return 0.0f;
        }
        return left / right;
    }

    return right;  // 无运算符时，输入什么就输出什么
}

void Widget::updateDisplay()
{
    // qDebug() << "updateDisplay\n";
    ui->lineEdit->setText(currentInput);
}

void Widget::resetAll()
{
    currentInput = "0";
    previousValue = 0.0f;
    currentOperator = "";
    resetNextInput = false;
    updateDisplay();
}

void Widget::onDigitClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    const QString text = btn->text();

    // 输入运算符之后重置屏幕输入新的数字
    if (resetNextInput) {
        currentInput = "";
        resetNextInput = false;
    }

    if (text == "00") {
        if (currentInput == "0" || currentInput.isEmpty()) {
            currentInput = "0";
            updateDisplay();
            return;
        }
        currentInput += "00";
        updateDisplay();
        return;
    }

    if (text == ".") {
        if (currentInput.contains(".")) {
            updateDisplay();
            return;
        }

        if (currentInput.isEmpty() || currentInput == "-") {
            currentInput += "0";
        }

        currentInput += ".";
        updateDisplay();
        return;
    }

    // 0-9
    if (currentInput == "0") {
        if (text != "0") {
            currentInput = text;
        }
    } else {
        currentInput += text;
    }

    updateDisplay();
}

void Widget::onOperatorClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString op = btn->text();
    double currentValue = currentInput.toDouble();

    if (!currentOperator.isEmpty()) {
        double result = calculate(previousValue, currentValue, currentOperator);
        currentInput = QString::number(result);
        previousValue = result;
    } else {
        previousValue = currentValue;
    }

    currentOperator = op;
    resetNextInput = true;
    updateDisplay();
}

void Widget::onEqualClicked()
{
    if (currentOperator.isEmpty()) {
        return ;
    }

    double currentValue = currentInput.toDouble();
    double result = calculate(previousValue, currentValue, currentOperator);

    currentInput = QString::number(result);
    updateDisplay();

    previousValue = 0.0f;
    currentOperator = "";
    resetNextInput = true;  // = 之后输入数字就清除当前结果（也是输入），输入运算符就把结果当做输入currentInput
}

void Widget::onClearClicked()
{
    resetAll();
}

void Widget::onBackspaceClicked()
{
    // 计算中间结果或最后结果时
    if (resetNextInput) {
        return ;
    }

    if (currentInput.length() > 1) {
        currentInput.chop(1);
    } else {
        currentInput = "0";
    }
    updateDisplay();
}

// 负变正  正变负
void Widget::onPlusMinusClicked()
{
    if (currentInput.isEmpty() || currentInput == "0") {
        return ;
    }

    if (currentInput.startsWith("-")) {
        currentInput.remove(0, 1);
    } else {
        currentInput.prepend("-");
    }
    updateDisplay();
}

void Widget::onPercentClicked()
{
    double val = currentInput.toDouble() / 100.0;
    currentInput = QString::number(val);
    updateDisplay();
}

void Widget::onMemoryClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    static double memoryValue = 0.0;

    QString text = btn->text();
    if (text == "MC") {
        memoryValue = 0.0;
        qDebug() << "Memory Cleared";
    } else if (text == "MR") {
        currentInput = QString::number(memoryValue);
        updateDisplay();
        qDebug() << "Memory Recall: " << memoryValue;
    } else if (text == "MS") {
        memoryValue = currentInput.toDouble();
        qDebug() << "Memory Stored: " << memoryValue;
    }
}


