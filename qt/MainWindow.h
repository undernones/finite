#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include <QtGui/QMainWindow>

class Ui_MainWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = NULL);
    ~MainWindow();

private:
    Ui_MainWindow* ui;
};

#endif // QT_MAINWINDOW_H
