#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colorcircle.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSlider        *m_slider;
    ColorCircle    *m_circle;
    QPushButton    *m_btnShowColor;
    QLabel         *m_lblColorInfo;
};
#endif // MAINWINDOW_H
