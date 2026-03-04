#include "logindialog.h"
#include "examdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog login_dialog;
    std::unique_ptr<ExamDialog> exam_dialog;
    // exec() 模态窗口，必须先处理当前Dialog(登录/取消)，有返回值
    int res { login_dialog.exec() };
    if (res == QDialog::Accepted) {
        // 登录进考试界面
        exam_dialog = std::make_unique<ExamDialog>();
    } else {
        return 0;
    }
    return a.exec();
}
