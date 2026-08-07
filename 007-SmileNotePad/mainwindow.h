#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void newActionSlot();
    void openActionSlot();
    void quickSaveActionSlot();
    void saveActionSlot();

private:
    Ui::MainWindow *ui;
    QString m_currentFilePath;
    const QString m_WindowTitle;
    QString getInitDir(QString filePath);
    bool m_newFile;
};
#endif // MAINWINDOW_H
