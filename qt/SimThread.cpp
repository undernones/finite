#include "SimThread.h"
#include "../World.h" // TODO: Dependencies!
#include <iostream>

SimThread::SimThread(QObject* parent) : QThread(parent),
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
        World::step(mDt);
        emit stepped();
    }
    std::cout << "done!" << std::endl;
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
