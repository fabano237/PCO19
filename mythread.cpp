#include "mythread.h"

long unsigned int MyThread::counter;
unsigned int MyThread::nbThreads;


MyThread::MyThread(long unsigned int paramNbIterations, const QString &threadName, QObject *parent) :
    QThread(parent)
{
    nbIterations = paramNbIterations;
    setObjectName(threadName);
}

void MyThread::initialize(unsigned int nbThreads)
{
    MyThread::nbThreads = nbThreads;
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
