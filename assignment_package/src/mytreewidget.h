#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include<QTreeWidget>
#include<QTreeWidgetItem>
#include "joint.h"

class Joint;

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
private:
    QString newJointName;
    Joint *selected;
public:
    MyTreeWidget(QWidget *p);
public slots:
    void slot_addJoint(QTreeWidgetItem*);
};

#endif // MYTREEWIDGET_H
