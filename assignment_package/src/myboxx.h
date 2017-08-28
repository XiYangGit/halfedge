#pragma once

#include <QDoubleSpinBox>
#include "vertexlistwidget.h"
#include "facelistwidget.h"


class MyBoxX : public QDoubleSpinBox
{
    Q_OBJECT
public:
    MyBoxX(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_VertexX(Vertex *p);
};



class MyBoxY : public QDoubleSpinBox
{
    Q_OBJECT
public:
    MyBoxY(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_VertexY(Vertex *p);
};


class MyBoxZ : public QDoubleSpinBox
{
    Q_OBJECT
public:
    MyBoxZ(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_VertexZ(Vertex *p);
};


class MyBoxR : public QDoubleSpinBox
{
    Q_OBJECT
public:
    MyBoxR(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_FaceR(Face *p);
};


class MyBoxG : public QDoubleSpinBox
{
    Q_OBJECT
public:
    MyBoxG(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_FaceG(Face *p);
};

class MyBoxB : public QDoubleSpinBox
{
    Q_OBJECT
public:
    MyBoxB(QWidget *p=NULL):QDoubleSpinBox(p){}
private slots:
    void slot_FaceB(Face *p);
};
