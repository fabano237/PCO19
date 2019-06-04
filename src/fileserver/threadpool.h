#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QList>
#include "QSemaphore"
#include "QMutex"
#include "QWaitCondition"
#include "runnable.h"
#include "workerthread.h"

class ThreadPool
{

private :
    //Nombre maximum de thread du threadPool
    const unsigned int maxThreadCount;

    //Liste des threads du threadPool
    QList<WorkerThread*> threadPool;
    QList<WorkerThread*> threadsDispo;
    QSemaphore wait;
    QMutex mutex; // protect local variable
    QWaitCondition condThreadDispo;
    bool hasDebugLog;

public:
    // constructor
    ThreadPool(unsigned int maxThreadCount);

    // destructor
    ~ThreadPool();

    /* Start a runnable. If a thread in the pool is available, handle &
    →the runnable with it. If no thread is available but the pool can &
    →grow, create a new pool thread and handle the runnable with it. If&
    → no thread is available and the pool is at max capacity, block the&
    → caller until a thread becomes available again. */
    void start(Runnable* runnable);

};

#endif // THREADPOOL_H
