#include "vertexlistwidget.h"
#include <QString>



void VertexlistWidget::slot_VertexItem(int VertexNum)
{
 clear();
for(int i=0;i<VertexNum;i++)
{

    addItem(QString::number(i));

}
}

void VertexlistWidget::slot_VertexXChanged(double x)
{

    emit sig_VertexXChanged(currentItem(),x);
}

void VertexlistWidget::slot_VertexYChanged(double x)
{

    emit sig_VertexYChanged(currentItem(),x);
}

void VertexlistWidget::slot_VertexZChanged(double x)
{

    emit sig_VertexZChanged(currentItem(),x);
}
void VertexlistWidget::slot_KeyPressH()
{
    emit sig_DrawHalfEdge(currentItem());
}
