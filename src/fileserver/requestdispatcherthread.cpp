#include <QDebug>
#include "requestdispatcherthread.h"
#include "requestthread.h"

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests to dispatch...";
        Request req = requests->get();  // block until we get an incoming request
        if (hasDebugLog)
            qDebug() << "Got a new request, spawning processing thread...";

        // Delete finished threads
        while ((workers.size() > 0) && (workers.at(0)->isFinished())){
            QThread *t = workers.at(0);
            workers.pop_front();
            delete t;
        }

        RequestThread* workerThread = new RequestThread(req, responses, hasDebugLog);
        workers.push_back(workerThread);
        workerThread->start();
    }
}
