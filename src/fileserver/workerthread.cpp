#include "workerthread.h"


void WorkerThread::assignRunnable(RunnableTask* task){
    this->task = task;
    task->run();
}

void WorkerThread::run(){
    while(true){
        task->run();

        mutex->lock();
        //Thread disponible
        threadsDispo->push_back(this);
        mutex->unlock();

        // Réveil du thread
        condThreadDispo->wakeOne();
        // attente du reveil
        wait->acquire();
    }
}
