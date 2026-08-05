#include "calculatordemo.h"
#include "ui_calculatordemo.h"
#include <limits>
#include <QMessageBox>

CalculatorDemo::CalculatorDemo(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::CalculatorDemo)
{
    ui->setupUi(this);
    expression = "";
    ui->lineEdit->setText(expression);

    // 按钮图标
    ui->btn_delete->setIcon(QIcon(":/icon_backspace.png"));

    // 改变=按钮背景色
    ui->btn_equal->setStyleSheet("background:#20be6f");

    // connect
    connect(ui->btn0, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn1, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn2, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn3, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn4, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn5, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn6, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn7, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn8, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn9, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn_plus, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn_minus, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn_multi, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn_divide, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn_lb, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn_rb, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();
    connect(ui->btn_point, &QPushButton::clicked, this, &CalculatorDemo::onBtnDigitAndOpClicked);    void on_btn_digit_and_op_clicked();

}

CalculatorDemo::~CalculatorDemo()
{
    delete ui;
}

void CalculatorDemo::UpdateDisplay()
{
    ui->lineEdit->setText(expression);
}

void CalculatorDemo::Mid2ReversExpr()
{
    QString tmp_text {""};
    for (const auto& e: std::as_const(expression)) {
        if ((e >= '0' && e <= '9') || e == '.') {
            tmp_text += e;
        } else if (e == '+' || e == '-' || e == '*' || e == '/' || e == '(') {
            if (!tmp_text.isEmpty()) {
                revers_expr_stack.push(tmp_text);
                tmp_text.clear();
            }
            if (e == '(' || op_stack.isEmpty() || getOpPrecedence(e) > getOpPrecedence(op_stack.top())) {
                op_stack.push(e);
            } else {
                // precedence e < op_stack top
                while (!op_stack.isEmpty() && getOpPrecedence(e) < getOpPrecedence(op_stack.top())) {
                    revers_expr_stack.push(op_stack.pop());
                }
                // reserve op
                op_stack.push(e);
            }
        } else if (e == ')') {
            if (!tmp_text.isEmpty()) {
                revers_expr_stack.push(tmp_text);
                tmp_text.clear();
            }
            while (op_stack.top() != '(') {
                revers_expr_stack.push(op_stack.pop());
            }
            op_stack.pop();  // remove '('
        }
    }
    if (!tmp_text.isEmpty()) {
        revers_expr_stack.push(tmp_text);
        tmp_text.clear();
    }
    while (!op_stack.isEmpty()) {
        revers_expr_stack.push(op_stack.pop());
    }

    // debug print
    // qDebug() << revers_expr_stack;
}

double CalculatorDemo::Calculator()
{
    number_stack.clear();

    while (!revers_expr_stack.isEmpty()) {
        QString token = revers_expr_stack.front();
        revers_expr_stack.pop_front();

        bool isNumber;
        double value = token.toDouble(&isNumber);

        if (isNumber) {
            number_stack.push(value);
        } else {
            // 至少要有2个操作数
            if (number_stack.size() < 2) {
                QMessageBox::warning(this, "错误", "操作数不足");
                return 0.0;
            }

            double b = number_stack.pop();   // 先弹出的是右操作数
            double a = number_stack.pop();

            double result = 0.0;
            QChar op = token[0];             // 运算符都是单字符
            switch (op.toLatin1()) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (fabs(b) <= std::numeric_limits<double>::epsilon()) {
                    QMessageBox::warning(this, "错误", "除零错误");
                    return 0.0;
                }
                result = a / b;
                break;
            default:
                QMessageBox::warning(this, "错误", "未知运算符");
                return 0.0;
            }
            number_stack.push(result);
        }
    }

    // 最终结果应该在栈顶，且栈内应只有一个元素
    if (number_stack.isEmpty()) {
        QMessageBox::warning(this, "错误", "表达式为空或格式错误");
        return 0.0;
    }
    return number_stack.pop(); // 弹出并返回，同时清空栈
}
int CalculatorDemo::getOpPrecedence(const QChar &op)
{
    switch (op.unicode()) {
    case '(':
        return 5;
    case '+':
    case '-':
        return 10;
    case '*':
    case '/':
        return 15;
    case '^':
        return 20;
    default:
        return 0;  // Invaild operator
    }
}

// 0-9 . + - * / ( )
void CalculatorDemo::onBtnDigitAndOpClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    const QString text { btn->text() };

    if (text == "." && expression.isEmpty()) {
        expression += "0";
    }

    expression += text;
    UpdateDisplay();
}
void CalculatorDemo::on_btn_C_clicked()
{
    expression.clear();
    UpdateDisplay();
}

void CalculatorDemo::on_btn_delete_clicked()
{
    expression.chop(1);
    UpdateDisplay();
}

void CalculatorDemo::on_btn_equal_clicked()
{
    Mid2ReversExpr();
    expression = QString::number(Calculator());
    UpdateDisplay();

    expression.clear();
    revers_expr_stack.clear();
    number_stack.clear();
    op_stack.clear();

}


