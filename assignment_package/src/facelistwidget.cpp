#include "facelistwidget.h"
#include <QString>

void FacelistWidget::slot_FaceItem(int FaceNum)
{
 clear();
for(int i=0;i<FaceNum;i++)
{

    addItem(QString::number(i));

}
}

void FacelistWidget::slot_FaceRChanged(double x)
{
    emit sig_FaceRChanged(currentItem(),x);
}
void FacelistWidget::slot_FaceGChanged(double x)
{
    emit sig_FaceGChanged(currentItem(),x);
}
void FacelistWidget::slot_FaceBChanged(double x)
{
    emit sig_FaceBChanged(currentItem(),x);
}

void FacelistWidget::slot_KeyPressShiftH()
{
    emit sig_DrawFaceHE(currentItem());
}

void FacelistWidget::slot_TriangulateClicked()
{
    emit sig_TriangulateFace(currentItem());
}

void FacelistWidget::slot_ExtrudeClicked()
{
    emit sig_ExtrudeFace(currentItem());
}
