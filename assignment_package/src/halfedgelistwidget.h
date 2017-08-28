#ifndef HALFEDGELISTWIDGET_H
#define HALFEDGELISTWIDGET_H
#include <QListWidget>
#include <QListWidgetItem>

class HalfEdgelistWidget : public QListWidget
{
    Q_OBJECT
public:
    HalfEdgelistWidget(QWidget *p=NULL):  QListWidget(p){}
private slots:
    void slot_HEItem(int HENum);
    void slot_KeyPressN();
    void slot_KeyPressM();
    void slot_KeyPressF();
    void slot_KeyPressV();
    void slot_AddVertexClicked();
signals:
    void sig_DrawNext(QListWidgetItem *p);
    void sig_DrawSym(QListWidgetItem *p);
    void sig_DrawFace(QListWidgetItem *p);
    void sig_DrawVertex(QListWidgetItem *p);
    void sig_AddVertex(QListWidgetItem *p);

};

#endif // HALFEDGELISTWIDGET_H
