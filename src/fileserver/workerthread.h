#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QDebug>
#include <QList>
#include <QVector>
#include <QSemaphore>
#include <QMutex>
#include <QWaitCondition>
#include "runnabletask.h"


class WorkerThread : public QThread
{

private:

    RunnableTask* task;
    QSemaphore* wait;
    QMutex* mutex;
    QList<WorkerThread*>* threadsDispo;
    QWaitCondition* condThreadDispo;
    int workerId;
    bool hasDebugLog;

public:

    WorkerThread(RunnableTask* task, QSemaphore* wait, QMutex* mutex, QList<WorkerThread*>* threadsDispo,
                 QWaitCondition* condThreadDispo, bool hasDebugLog){
        this->task = task;
        this->wait = wait;
        this->mutex= mutex;
        this->threadsDispo = threadsDispo;
        this->condThreadDispo = condThreadDispo;
        this->hasDebugLog = hasDebugLog;
    }

    ~WorkerThread() {}

    void assignRunnable(RunnableTask* task);

    void run();
};

#endif // WORKERTHREAD_H
