#ifndef DYNAMICPROPERTYDIALOG_H
#define DYNAMICPROPERTYDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include "colorcircle.h"

class DynamicPropertyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DynamicPropertyDialog(QWidget* parent = nullptr);

private slots:
    void onColorInput();

private:
    ColorCircle    *m_circle;
    QSlider        *m_slider;
    QLabel         *m_lblColorInfo;
    QPushButton    *m_btnShowColor;
};

#endif // DYNAMICPROPERTYDIALOG_H
