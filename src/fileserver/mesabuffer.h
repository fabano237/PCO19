#ifndef MESABUFFER_H
#define MESABUFFER_H

#include "abstractbuffer.h"
#include <QMutex>
#include <QWaitCondition>

template<typename T>
class MesaBuffer : public AbstractBuffer<T> {
private:
    QMutex mutex;
    QWaitCondition full;
    QWaitCondition empty;
    T *elements;
    unsigned int bufferSize;
    unsigned int readPointer = 0;
    unsigned int writePointer = 0;
    unsigned int nbElements = 0;

    int isFull() {
        return nbElements == bufferSize;
    }

    int isEmpty() {
        return nbElements == 0;
    }

    void incrementPointer(unsigned int &pointer) {
        pointer = (pointer + 1) % bufferSize;
    }

public:
    MesaBuffer(unsigned int bufferSize) {
        this->bufferSize = bufferSize;
        this->elements = new T[bufferSize];
        this->bufferSize = bufferSize;
    }

    virtual ~MesaBuffer() {}

    virtual void put(T item) {
        mutex.lock();
        while (isFull()) {
            full.wait(&mutex);
        }
        elements[writePointer] = item;
        incrementPointer(writePointer);
        nbElements++;
        empty.wakeOne();
        mutex.unlock();
    }

    virtual T get(void) {
        T item;
        mutex.lock();
        while (isEmpty()){
            empty.wait(&mutex);
        }
        item = elements[readPointer];
        incrementPointer(readPointer);
        nbElements--;
        full.wakeOne();
        mutex.unlock();
        return item;
    }
};

#endif // MESABUFFER_H
