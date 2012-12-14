#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include <QtGui/QMainWindow>

class SoftBody;
class Ui_MainWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = NULL);
    ~MainWindow();

    void setSoftBody(const SoftBody* body);

private:
    Ui_MainWindow* ui;

public slots:
    void paused();
    void resumed();
    void stepped();
};

#endif // QT_MAINWINDOW_H
