#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QBoxLayout>
#include <QList>

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

private slots:
    void openDynamicProperDemo();
    void openLabelDemo();

private:
    Ui::MainWindow    *ui;
    QPushButton       *m_btnDynamic;
    QPushButton       *m_btnLabel;

    QList<QWidget*>   m_demos;
    void addStyleButton(QBoxLayout *layout, QPushButton *btn, const QString &text, int fixed_width = 72);
};
#endif // MAINWINDOW_H
