#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SimThread.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui_MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionPlay, SIGNAL(triggered()), &SimThread::instance(), SLOT(resume()));
    connect(ui->actionPause, SIGNAL(triggered()), &SimThread::instance(), SLOT(pause()));
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

