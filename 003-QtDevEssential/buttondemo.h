#ifndef BUTTONDEMO_H
#define BUTTONDEMO_H

#include <QObject>
#include <QWidget>

class ButtonDemo : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonDemo(QWidget *parent = nullptr);
};

#endif // BUTTONDEMO_H
