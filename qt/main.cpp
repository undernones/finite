#include <QtGui/QApplication>
#include "MainWindow.h"
#include "SimThread.h"
#include "../Options.h" // TODO: dependencies!
#include "../World.h" // TODO: dependencies!

int main(int argc, char* argv[])
{
    Options::init(argc, argv);
    World::init(Options::meshFile());

    SimThread& thread(SimThread::instance());

    QApplication a(argc, argv);
    MainWindow w;
    w.setSoftBody(&World::softBody());
    w.connect(&thread, SIGNAL(stepped()), SLOT(stepped()));
    w.raise();
    w.show();

    thread.init(Options::duration(), Options::dt());
    thread.start(QThread::NormalPriority);

    return a.exec();
}
