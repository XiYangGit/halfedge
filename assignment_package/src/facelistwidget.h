#ifndef FACELISTWIDGET_H
#define FACELISTWIDGET_H
#include <QListWidget>
#include <QListWidgetItem>

class FacelistWidget : public QListWidget
{
    Q_OBJECT
public:
    FacelistWidget(QWidget *p=NULL):  QListWidget(p){}
private slots:
    void slot_FaceItem(int FaceNum);
    void slot_FaceRChanged(double x);
    void slot_FaceGChanged(double x);
    void slot_FaceBChanged(double x);
    void slot_KeyPressShiftH();
    void slot_TriangulateClicked();
    void slot_ExtrudeClicked();
signals:
    void sig_FaceRChanged(QListWidgetItem *p,double x);
    void sig_FaceGChanged(QListWidgetItem *p,double x);

    void sig_FaceBChanged(QListWidgetItem *p,double x);

    void sig_DrawFaceHE(QListWidgetItem *p);

    void sig_TriangulateFace(QListWidgetItem *p);

    void sig_ExtrudeFace(QListWidgetItem *p);
};

#endif // FACELISTWIDGET_H
