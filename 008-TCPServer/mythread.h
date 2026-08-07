#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QTcpSocket* s);

protected:
    void run() override;

signals:

private slots:
    void clntInfoSlot();

private:
    QTcpSocket* socket;
};

#endif // MYTHREAD_H
