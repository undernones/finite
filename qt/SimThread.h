#ifndef VIEWER_SIMTHREAD_H
#define VIEWER_SIMTHREAD_H

#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

class SimThread : public QThread
{
    Q_OBJECT

public:
    static SimThread& instance();
    ~SimThread();

    static void setTimeParams(double duration, double dt);
    static bool isPaused();

protected:
    void run();

private:
    QMutex mMutex;
    QWaitCondition mWaitCondition;
    bool mIsPaused;
    bool mQuitFlag;
    double mDuration;
    double mDt;

    explicit SimThread(QObject* parent = NULL);
    SimThread(const SimThread&);

signals:
    void paused();
    void resumed();
    void stepped();

public slots:
    void quit();
    void togglePausedState();
    void pause();
    void resume();
    void step();
};

#endif // VIEWER_SIMTHREAD_H
