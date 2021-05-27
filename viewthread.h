#ifndef VIEWTHREAD_H
#define VIEWTHREAD_H
#include <QThread>

class Renderer;

class ViewThread : public QThread {
    protected:
        int threadsRemaining;

    public:
        ViewThread();
        ViewThread(QObject *parent);
        ViewThread(const ViewThread &thread) = delete;
        ViewThread& operator=(const ViewThread &thread) = delete;
        virtual ~ViewThread();

        void run();
        void setThreadsRemaining(int value);
        int getThreadsRemaining();
};

#endif // VIEWTHREAD_H
