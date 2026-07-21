#include "widget.h"

#include <QApplication>

// Qt 网格布局(我使用水平+垂直布局)，STL容器
/*
currentInput	QString	当前显示屏上显示的数字（文本）
previousValue	double	上一次参与运算的数字
currentOperator	QString	当前按下的运算符（+、-、×、÷）
resetNextInput	bool	按了运算符后，下一个数字需要重置屏幕（关键标志）
*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return QCoreApplication::exec();
}
