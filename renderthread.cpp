#include "renderthread.h"
#include "renderer.h"

RenderThread::RenderThread() : QThread(NULL), y(0), lineSize(1) {
    initArray();
}

RenderThread::RenderThread(QObject *parent, int lineSize) : QThread(parent), y(0), lineSize(lineSize) {
    initArray();
}

RenderThread::~RenderThread() {
    clearArray();
}

void RenderThread::setY(int y) {
    this->y = y;
}

int RenderThread::getY() {
    return y;
}

QColor* RenderThread::getLine() {
    return line;
}

void RenderThread::run() {
    if(!isInterruptionRequested()) {
        Renderer *renderer = dynamic_cast<Renderer*>(parent());
        renderer->renderLine(line, y);
        renderer->insertLine(line, lineSize, y);
    }
}

void RenderThread::initArray() {
    line = new QColor[lineSize];
    for(int i = 0; i < lineSize; i++) {
        line[i] = nullptr;
    }
}

void RenderThread::clearArray() {
    delete [] line;
}

void RenderThread::setLineSize(int size) {
    clearArray();
    this->lineSize = size;
    initArray();
}

int RenderThread::getLineSize() {
    return lineSize;
}
