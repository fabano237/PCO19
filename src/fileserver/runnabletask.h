#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H

#include "runnable.h"
#include "request.h"
#include "abstractbuffer.h"
#include "requesthandler.h"
#include "requesthandler.h"

#include <QDebug>

class RunnableTask : public Runnable {

private:

    QString idTask;
    Request* request;                    //requêtes pour le workerthread
    AbstractBuffer<Response>* responses; //Buffer de reponse pour requêtes traités
    RequestHandler* requestHandler;      //recuperation de la reponse d'une requête
    bool hasDebugLog;                    //pour le debug


public:
    RunnableTask(QString idTask, Request* request,  AbstractBuffer<Response>* responses, bool hasDebugLog);

    Request* getRequest();

    ~RunnableTask();

    void run();

    QString id();
};

#endif // RUNNABLETASK_H
