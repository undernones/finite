#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include <QtGui/QMainWindow>

class Mesh;
class Ui_MainWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = NULL);
    ~MainWindow();

    void setMesh(const Mesh* mesh);

private:
    Ui_MainWindow* ui;

public slots:
    void stepped();
};

#endif // QT_MAINWINDOW_H
