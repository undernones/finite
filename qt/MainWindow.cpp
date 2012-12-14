#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SimThread.h"
#include "../World.h" // TODO: Dependencies!

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui_MainWindow)
{
    ui->setupUi(this);

    SimThread& thread(SimThread::instance());

    connect(ui->actionPlayPause, SIGNAL(triggered()), &thread, SLOT(togglePausedState()));
    connect(ui->actionNext, SIGNAL(triggered()), &thread, SLOT(step()));

    connect(&thread, SIGNAL(paused()), SLOT(paused()));
    connect(&thread, SIGNAL(resumed()), SLOT(resumed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setSoftBody(const SoftBody* body)
{
    const Mesh* mesh = NULL;
    const Eigen::Matrix3d* matrix = NULL;

    if (body != NULL) {
        mesh = &body->mesh();
        matrix = &body->deformations()[0];
    }

    ui->glWidget->setMesh(mesh);
    ui->matrixViewer->setMatrix(matrix);
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

    // Only update the matrix viewer if we are stepping interactively.
    if (SimThread::instance().isPaused()) {
        ui->matrixViewer->refresh();
    }
}
