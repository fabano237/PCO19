#include "threadpool.h"

ThreadPool::ThreadPool(unsigned int maxThreadCount): maxThreadCount(maxThreadCount){

}

ThreadPool::~ThreadPool(){

    const int size = threadPool.size();
    WorkerThread* tmp;
    for(int i = 0; i < size; ++i){
        tmp = threadPool.front();
        tmp->terminate();
        threadPool.pop_front();
        delete tmp;
    }

}

/* Start a runnable. If a thread in the pool is avaible, assign the
    runnable to it. If no thread is available but the pool can grow,
    create a new pool thread and assign the runnable to it. If no
    thread is available and the pool is at max capacity, block the
    caller until a thread becomes available again.*/
void ThreadPool::start(Runnable* runnable) {

    mutex.lock();

    /* if the threadPool is not full, we create a new thread and push it in the pool. */
    if(threadPool.size() < int(maxThreadCount)){
        WorkerThread* worker = new WorkerThread((RunnableTask*) runnable, &wait, &mutex, &threadsDispo, &condThreadDispo, hasDebugLog);
        threadPool.push_back(worker);
        worker->start();
    }else{

        if(!threadsDispo.size()){
            condThreadDispo.wait(&mutex);
        }

        threadsDispo.front()->assignRunnable((RunnableTask*) runnable);
        wait.release();
        threadsDispo.pop_front();
    }
    mutex.unlock();
}
