#ifndef COLORINPUTDIALOG_H
#define COLORINPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ColorInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ColorInputDialog(QWidget* parent = nullptr);
    QColor getColor() const;

private:
    QLineEdit* m_lineEdit;
};

#endif // COLORINPUTDIALOG_H
