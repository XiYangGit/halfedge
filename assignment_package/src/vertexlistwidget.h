#ifndef VERTEXLISTWIDGET_H
#define VERTEXLISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include "vertex.h"
class Vertex;

class VertexlistWidget : public QListWidget
{
    Q_OBJECT

public:
    VertexlistWidget(QWidget *p=NULL):  QListWidget(p){}
private slots:
    void slot_VertexItem(int VertexNum);
    void slot_VertexXChanged(double x);
    void slot_VertexYChanged(double x);
    void slot_VertexZChanged(double x);

    void slot_KeyPressH();
signals:
    void sig_VertexXChanged(QListWidgetItem *p,double x);
    void sig_VertexYChanged(QListWidgetItem *p,double x);

    void sig_VertexZChanged(QListWidgetItem *p,double x);


    void sig_DrawHalfEdge(QListWidgetItem *p);

};

#endif // VERTEXLISTWIDGET_H
