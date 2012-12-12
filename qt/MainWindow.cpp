#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SimThread.h"
#include "../World.h" // TODO: Dependencies!

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui_MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionPlayPause,    SIGNAL(triggered()),
            &SimThread::instance(), SLOT(togglePausedState()));

    connect(ui->actionNext, SIGNAL(triggered()),
            &SimThread::instance(), SLOT(step()));

    connect(&SimThread::instance(), SIGNAL(paused()), SLOT(paused()));
    connect(&SimThread::instance(), SIGNAL(resumed()), SLOT(resumed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setMesh(const Mesh* mesh)
{
    ui->glWidget->setMesh(mesh);
}

void
MainWindow::setSimData(const SimData* simData)
{
    const Eigen::Matrix3d* mat = NULL;
    if (simData != NULL) {
        mat = &simData->deformations[0];
    }
    ui->matrixViewer->setMatrix(mat);
}

void
MainWindow::paused()
{
    ui->actionNext->setEnabled(true);
}

void
MainWindow::resumed()
{
    ui->actionNext->setEnabled(false);
}

void
MainWindow::stepped()
{
    ui->glWidget->update();
    //ui->matrixViewer->refresh();
}
