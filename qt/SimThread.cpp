#include "SimThread.h"
#include "../World.h" // TODO: Dependencies!

SimThread::SimThread(QObject* parent) : QThread(parent),
    mPaused(false),
    mQuitFlag(false),
    mDuration(0),
    mDt(0)
{
}

SimThread::~SimThread()
{
}

SimThread&
SimThread::instance()
{
    static SimThread inst;
    return inst;
}

void
SimThread::run()
{
    static uint32_t totalSteps = mDuration / mDt;
    for (uint32_t i = 0; i < totalSteps && !mQuitFlag; ++i) {
        mMutex.lock();
        if (mPaused) {
            mWaitCondition.wait(&mMutex);
        }
        mMutex.unlock();

        World::step(mDt);
        emit stepped();
    }
}

void
SimThread::quit()
{
    mQuitFlag = true;
    QThread::quit();
}

void
SimThread::setTimeParams(double duration, double dt)
{
    instance().mDuration = duration;
    instance().mDt = dt;
}

void
SimThread::pause()
{
    mMutex.lock();
    mPaused = true;
    mMutex.unlock();
}

void
SimThread::resume()
{
    mMutex.lock();
    mPaused = false;
    mMutex.unlock();
    mWaitCondition.wakeAll();
}

