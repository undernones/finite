#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SimThread.h"

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
MainWindow::setSimData(const SimData* mesh)
{
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
    ui->glWidget->repaint();
}
