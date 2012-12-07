#include "SimThread.h"
#include "../World.h" // TODO: Dependencies!

SimThread::SimThread(QObject* parent) : QThread(parent),
    mIsPaused(false),
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
    while (!mQuitFlag) {
        mMutex.lock();
        if (mIsPaused) {
            mWaitCondition.wait(&mMutex);
        }
        mMutex.unlock();
        step();
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

bool
SimThread::isPaused()
{
    return instance().mIsPaused;
}

void
SimThread::togglePausedState()
{
    if (mIsPaused) {
        resume();
    } else {
        pause();
    }
}

void
SimThread::pause()
{
    mMutex.lock();
    mIsPaused = true;
    mMutex.unlock();
    emit paused();
}

void
SimThread::resume()
{
    mMutex.lock();
    mIsPaused = false;
    mMutex.unlock();
    mWaitCondition.wakeAll();
    emit resumed();
}

void
SimThread::step()
{
    static uint32_t totalSteps = mDuration / mDt;
    static uint32_t i = 0;
    if (i < totalSteps) {
        World::step(mDt);
        emit stepped();
    }
}
