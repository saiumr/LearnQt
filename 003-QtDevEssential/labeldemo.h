#ifndef LABELDEMO_H
#define LABELDEMO_H

#include <QWidget>

class LabelDemo : public QWidget
{
    Q_OBJECT
public:
    explicit LabelDemo(QWidget *parent = nullptr);
    ~LabelDemo();
};

#endif // LABELDEMO_H
