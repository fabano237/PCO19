#include "runnabletask.h"

RunnableTask::RunnableTask(QString idTask, Request* request,  AbstractBuffer<Response>* responses, bool hasDebugLog): idTask(idTask), request(request), responses(responses), hasDebugLog(hasDebugLog){
    requestHandler = new RequestHandler(*request ,hasDebugLog);
}

Request* RunnableTask::getRequest(){
    return request;
}

RunnableTask::~RunnableTask() {
    delete requestHandler;
}

void RunnableTask::run(){
    //Récupération de la réponse de la requête
    Response response = requestHandler->handle();
    //QInfo() << response.getResponse().toStdString() << ;
    //reponse au buffer de reponse
    responses->put(response);
}

QString RunnableTask::id(){
    return idTask;
}
