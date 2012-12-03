#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui_MainWindow)
{
    ui->setupUi(this);
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
