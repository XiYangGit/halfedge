#pragma once
#include <QDoubleSpinBox>
#include "mytreewidget.h"

class JointBoxPosX:public QDoubleSpinBox
{
    Q_OBJECT
public:
    JointBoxPosX(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_JointPosX(float);
};

class JointBoxPosY:public QDoubleSpinBox
{
    Q_OBJECT
public:
    JointBoxPosY(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_JointPosY(float);
};
class JointBoxPosZ:public QDoubleSpinBox
{
    Q_OBJECT
public:
    JointBoxPosZ(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_JointPosZ(float);
};


//class JointBoxRotW:public QDoubleSpinBox
//{
//    Q_OBJECT
//public:
//    JointBoxRotW(QWidget *p=NULL):QDoubleSpinBox(p){}
//private slots:
//    void slot_JointRotW(float);
//};
//class JointBoxRotX:public QDoubleSpinBox
//{
//    Q_OBJECT
//public:
//    JointBoxRotX(QWidget *p=NULL):QDoubleSpinBox(p){}
//private slots:
//    void slot_JointRotX(float);
//};
//class JointBoxRotY:public QDoubleSpinBox
//{
//    Q_OBJECT
//public:
//    JointBoxRotY(QWidget *p=NULL):QDoubleSpinBox(p){}
//private slots:
//    void slot_JointRotY(float);
//};
//class JointBoxRotZ:public QDoubleSpinBox
//{
//    Q_OBJECT
//public:
//    JointBoxRotZ(QWidget *p=NULL):QDoubleSpinBox(p){}
//private slots:
//    void slot_JointRotZ(float);
//};

