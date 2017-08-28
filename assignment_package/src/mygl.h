#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include <scene/spoint.h>
#include <scene/sline.h>
#include <scene/sface.h>
#include <scene/jsphere.h>
#include <scene/jline.h>
#include "mesh.h"
#include "camera.h"
#include "vertexlistwidget.h"
#include <QListWidget>
#include <QListWidgetItem>
#include "joint.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


class MyGL
    : public GLWidget277
{
    Q_OBJECT
private:
    Cylinder geom_cylinder;// The instance of a unit cylinder we can use to render any cylinder
    Sphere geom_sphere;// The instance of a unit sphere we can use to render any sphere
    Mesh geom_mesh; //add by Xi Yang
    sPoint geom_spoint;  //add by Xi Yang
    sLine geom_sline;    //add by Xi Yang
    sFace geom_sface;    //add by Xi Yang
    JSphere geom_Jsphere;   //add by Xi Yang
    JLine geom_Jline;     //add by Xi Yang
    ShaderProgram prog_lambert;// A shader program that uses lambertian reflection
    ShaderProgram prog_flat;// A shader program that uses "flat" reflection (no shadowing at all)

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera gl_camera;

    /// Timer linked to timerUpdate(). Fires approx. 60 times per second
    QTimer timer;
    int timeCount;
    int renderMode;

    //added by Xi Yang
    HalfEdge* selected_he;
    Joint* rootjoint;
    Joint* selected_joint;
    ShaderProgram prog_skeleton;
    int shaderMode;


public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void LoadObj(std::vector<glm::vec3> vert_pos,std::vector<glm::vec2> vert_vt,
                 std::vector<glm::vec3> vert_nor,std::vector<std::vector<glm::vec3>> faceVector);

    void drawAndSelectNextEdge();
    void drawAndSelectSymEdge();

    void SetRootJoint(Joint*);

    Joint* CreateFromJson(QJsonObject);
    void DrawJoint(Joint*);
    void updateBindMatrices();
    void updateTransformations();

    void clearmeshjoints();

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    /// Slot that gets called ~60 times per second
    virtual void timerUpdate();
    void slot_VertexHighlight(QListWidgetItem *p);
    void slot_EdgeHighlight(QListWidgetItem *p);
    void slot_FaceHighlight(QListWidgetItem *p);
    void slot_VertexXChanged(QListWidgetItem *p,double x);
    void slot_VertexYChanged(QListWidgetItem *p,double x);
    void slot_VertexZChanged(QListWidgetItem *p,double x);
    void slot_FaceRChanged(QListWidgetItem *p,double x);
    void slot_FaceGChanged(QListWidgetItem *p,double x);
    void slot_FaceBChanged(QListWidgetItem *p,double x);



    void slot_DrawNext(QListWidgetItem *p);
    void slot_DrawSym(QListWidgetItem *p);
    void slot_DrawFace(QListWidgetItem *p);
    void slot_DrawVertex(QListWidgetItem *p);
    void slot_DrawHalfEdge(QListWidgetItem *p);
    void slot_DrawFaceHE(QListWidgetItem *p);



    void slot_AddVertex(QListWidgetItem *p);
    void slot_TriangulateFace(QListWidgetItem *p);
    void slot_Subdivision();

    void slot_ExtrudeFace(QListWidgetItem *p);

    void slot_Skinning();

    void slot_JointClicked(QTreeWidgetItem *n, int i);
    void slot_JointPosXChanged(double x);
    void slot_JointPosYChanged(double x);
    void slot_JointPosZChanged(double x);
//    void slot_JointRotWChanged(double x);
//    void slot_JointRotXChanged(double x);
//    void slot_JointRotYChanged(double x);
//    void slot_JointRotZChanged(double x);
    void slot_RotateX_1();
    void slot_RotateX_2();
    void slot_RotateY();
    void slot_RotateY_();
    void slot_RotateZ();
    void slot_RotateZ_();


signals:
    void sig_VertexItem(int VertexNum);
    void sig_FaceItem(int FaceNum);
    void sig_HEItem(int HENum);
    void sig_VertexX(Vertex *v);
    void sig_VertexY(Vertex *v);
    void sig_VertexZ(Vertex *v);
    void sig_FaceR(Face *f);
    void sig_FaceG(Face *f);
    void sig_FaceB(Face *f);
    void sig_KeyPressN();
    void sig_KeyPressM();
    void sig_KeyPressF();
    void sig_KeyPressV();
    void sig_KeyPressH();
    void sig_KeyPressShiftH();

    void sig_SendJoint(QTreeWidgetItem*);
    void sig_JointPosX(float);
    void sig_JointPosY(float);
    void sig_JointPosZ(float);
//    void sig_JointRotW(float);
//    void sig_JointRotX(float);
//    void sig_JointRotY(float);
//    void sig_JointRotZ(float);
    void sig_ShowLocalTrans(Joint*);
    void sig_ShowRotation(Joint*);



};


#endif // MYGL_H
