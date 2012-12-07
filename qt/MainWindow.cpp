#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SimThread.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui_MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionPlayPause, SIGNAL(triggered()), SLOT(togglePlayPause()));
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
MainWindow::stepped()
{
    ui->glWidget->repaint();
}

void
MainWindow::togglePlayPause()
{
    if (SimThread::isPaused()) {
        SimThread::instance().resume();
        ui->actionNext->setEnabled(false);
    } else {
        SimThread::instance().pause();
        ui->actionNext->setEnabled(true);
    }
}
