#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include <QtGui/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = NULL);
    ~MainWindow();
};

#endif // QT_MAINWINDOW_H
