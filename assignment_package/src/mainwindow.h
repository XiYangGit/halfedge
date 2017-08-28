#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vertexlistwidget.h"
#include <QListWidget>
#include <QListWidgetItem>
#include "mesh.h"
#include "mygl.h"
#include <la.h>
#include <glm/glm.hpp>


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
    void on_actionQuit_triggered();

    void on_actionCamera_Controls_triggered();

    void on_actionLoad_OBJ_triggered();

    void on_actionLoad_Json_File_triggered();

    void slot_ShowLocalTrans(Joint*);

    void slot_ShowRotation(Joint*);



private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
