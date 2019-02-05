#include "mythread.h"

long unsigned int MyThread::counter;

MyThread::MyThread(long unsigned int paramNbIterations, const QString &threadName, QObject *parent) :
    QThread(parent)
{
    nbIterations = paramNbIterations;
    setObjectName(threadName);
}

void MyThread::run()
{
    long unsigned int i = 0;

    while (i < nbIterations)
    {
        counter++;
        i++;
    }
}
