#ifndef DYNAMICPROPERTYDEMO_H
#define DYNAMICPROPERTYDEMO_H

#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include "colorcircle.h"

class DynamicPropertyDemo : public QWidget
{
    Q_OBJECT
public:
    explicit DynamicPropertyDemo(QWidget* parent = nullptr);
    ~DynamicPropertyDemo();

private slots:
    void onColorInput();

private:
    ColorCircle    *m_circle;
    QSlider        *m_slider;
    QLabel         *m_lblColorInfo;
    QPushButton    *m_btnShowColor;
};

#endif // DYNAMICPROPERTYDEMO_H
