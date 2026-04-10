#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QBoxLayout>
#include <QList>
#include <QWidget>
#include <QPointer>

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
    void openButtonDemo();
    void openLineEditDemo();

signals:
    void sigCloseAllDemos();  // 广播关闭信号

private:
    Ui::MainWindow    *ui;
    QPushButton       *m_btnDynamic;
    QPushButton       *m_btnLabel;
    QPushButton       *m_btnButton;
    QPushButton       *m_btnLineEdit;

    QList<QPointer<QWidget>> m_demos;
    void closeEvent(QCloseEvent *event) override;
    void addStyleButton(QBoxLayout *layout, QPushButton *btn, const QString &text, int fixed_width = 72);
    void setButtonBh(QWidget *demo);
};
#endif // MAINWINDOW_H
