#include <iostream>

#include "requestthread.h"
#include "requesthandler.h"

void RequestThread::run()
{
    Response resp = RequestHandler(this->req, this->hasDebugLog).handle();
    this->responses->put(resp);
    exit(0);
}



RequestThread::~RequestThread()
{
    std::cout << "Killing a thread" << std::endl;
}
