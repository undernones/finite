#ifndef VIEWER_SIMTHREAD_H
#define VIEWER_SIMTHREAD_H

#include <QtCore/QThread>

class SimThread : public QThread
{
    Q_OBJECT

public:
    static SimThread& instance();
    ~SimThread();

    static void setTimeParams(double duration, double dt);

protected:
    void run();

private:
    bool mQuitFlag;
    double mDuration;
    double mDt;

    explicit SimThread(QObject* parent = NULL);
    SimThread(const SimThread&);

signals:
    void stepped();

public slots:
    void quit();
};

#endif // VIEWER_SIMTHREAD_H
