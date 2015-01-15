#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionReload_Shaders_triggered();

    void on_actionLoad_Mesh_triggered();

    void onResolutionSettingsChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
