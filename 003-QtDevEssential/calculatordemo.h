#ifndef CALCULATORDEMO_H
#define CALCULATORDEMO_H

#include <QWidget>
#include <QString>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui {
class CalculatorDemo;
}
QT_END_NAMESPACE

class CalculatorDemo : public QWidget
{
    Q_OBJECT
public:
    explicit CalculatorDemo(QWidget *parent = nullptr);
    ~CalculatorDemo();

private:
    Ui::CalculatorDemo *ui;
    QString expression;
    QStack<QString> revers_expr_stack;
    QStack<double> number_stack;
    QStack<QChar> op_stack;
    void UpdateDisplay();
    int  getOpPrecedence(const QChar& op);
    void Mid2ReversExpr();
    double Calculator();

signals:
private slots:
    void onBtnDigitAndOpClicked();
    void on_btn_equal_clicked();
    void on_btn_C_clicked();
    void on_btn_delete_clicked();
};

#endif // CALCULATORDEMO_H
