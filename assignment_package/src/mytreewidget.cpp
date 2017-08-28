#include "mytreewidget.h"

MyTreeWidget::MyTreeWidget(QWidget *p):QTreeWidget(p),newJointName(),selected(nullptr)
{

}

void MyTreeWidget::slot_addJoint(QTreeWidgetItem *j)
{
    clear();
    addTopLevelItem(j);
}
