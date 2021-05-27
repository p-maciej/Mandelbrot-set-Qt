#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H
#include <QThread>
#include <QObject>
#include <QColor>
#include <QPainter>


class Renderer;

class RenderThread : public QThread {
    protected:
        QColor* line;
        int y;
        int lineSize;

    public:
        RenderThread();
        RenderThread(QObject *parent, int lineSize);
        RenderThread(const RenderThread &thread) = delete;
        RenderThread& operator=(const RenderThread &thread) = delete;
        virtual ~RenderThread();

        void setY(int y);
        void setLineSize(int size);
        int getY();
        int getLineSize();
        QColor* getLine();
        void run();

    private:
        void initArray();
        void clearArray();
};

#endif // RENDERTHREAD_H
