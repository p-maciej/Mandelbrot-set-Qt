#include "viewthread.h"
#include "renderer.h"

ViewThread::ViewThread() : QThread(NULL) {}
ViewThread::ViewThread(QObject *parent) : QThread(parent) {}
ViewThread::~ViewThread() {}

void ViewThread::setThreadsRemaining(int value) {
    this->threadsRemaining = value;
}

int ViewThread::getThreadsRemaining() {
    return threadsRemaining;
}

void ViewThread::run() {
    if(!isInterruptionRequested()) {
        while(threadsRemaining > 0) {
            Renderer *renderer = dynamic_cast<Renderer*>(parent());
            renderer->threadUpdate();
            this->msleep(100);
        }
    }
}
