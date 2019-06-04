#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H
#include <QThread>
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"

class RequestThread: public QThread
{
private:
    Request req;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;

public:
    RequestThread(Request req, AbstractBuffer<Response>* responses, bool hasDebugLog): req(req), responses(responses), hasDebugLog(hasDebugLog) {}

    virtual ~RequestThread();

protected:
    void run();
};

#endif // REQUESTTHREAD_H
