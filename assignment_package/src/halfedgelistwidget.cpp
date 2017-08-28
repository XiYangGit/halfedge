#include "halfedgelistwidget.h"
#include <halfedge.h>
#include <QString>

void HalfEdgelistWidget::slot_HEItem(int HENum)
{
    clear();

for(int i=0;i<HENum;i++)
{


    addItem(QString::number(i));

}
}
void HalfEdgelistWidget::slot_KeyPressN()
{
//    setCurrentItem((QListWidgetItem*)(((HalfEdge*)(currentItem()))->GetNext()));
    emit sig_DrawNext(currentItem());
}

void HalfEdgelistWidget::slot_KeyPressM()
{
    emit sig_DrawSym(currentItem());
}
void HalfEdgelistWidget::slot_KeyPressF()
{
    emit sig_DrawFace(currentItem());
}
void HalfEdgelistWidget::slot_KeyPressV()
{
    emit sig_DrawVertex(currentItem());
}

void HalfEdgelistWidget::slot_AddVertexClicked()
{
    emit sig_AddVertex(currentItem());
}
