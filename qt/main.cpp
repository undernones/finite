#include <QtGui/QApplication>
#include "MainWindow.h"
#include "SimThread.h"
#include "../Options.h" // TODO: dependencies!
#include "../World.h" // TODO: dependencies!

int main(int argc, char* argv[])
{
    Options::init(argc, argv);
    World::init(Options::meshFile());

    QApplication a(argc, argv);
    MainWindow w;
    w.raise();
    w.show();

    // TODO: Connect the GlWidget to the SimThread stepped signal.
    // TODO: SimThread interface consistency!
    SimThread::setTimeParams(Options::duration(), Options::dt());
    SimThread::instance().start(QThread::NormalPriority);

    return a.exec();
}
