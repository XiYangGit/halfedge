#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>


MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent),
      geom_cylinder(this), geom_sphere(this),geom_mesh(this),
      geom_spoint(this),geom_sline(this),geom_sface(this),
      geom_Jsphere(this),geom_Jline(this),
      prog_lambert(this), prog_flat(this),
      gl_camera(),timeCount(0),renderMode(0),
      selected_he(nullptr),rootjoint(nullptr),selected_joint(nullptr),
      prog_skeleton(this),shaderMode(0)
{
    // Connect the timer to a function so that when the timer ticks the function is executed
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    // Tell the timer to redraw 60 times per second
    timer.start(16);

    setFocusPolicy(Qt::ClickFocus);
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    geom_cylinder.destroy();
    geom_sphere.destroy();
    geom_mesh.destroy();
    geom_spoint.destroy();
    geom_sline.destroy();
    geom_sface.destroy();
    geom_Jsphere.destroy();
    geom_Jline.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instances of Cylinder and Sphere.
    geom_cylinder.create();

    geom_sphere.create();

    geom_mesh.CreatCube();
    geom_mesh.create();
    emit sig_VertexItem(geom_mesh.GetVertexNum());
    emit sig_FaceItem(geom_mesh.GetFaceNum());
    emit sig_HEItem(geom_mesh.GetEgdeNum());

    geom_spoint.create();
    geom_sline.create();
    geom_sface.create();
    geom_Jsphere.create();
    geom_Jline.create();
    // Create and set up the diffuse shader
    prog_lambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    prog_flat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    prog_skeleton.create(":/glsl/skeleton.vert.glsl", ":/glsl/skeleton.frag.glsl");
    // Set a color with which to draw geometry since you won't have one
    // defined until you implement the Node classes.
    // This makes your geometry render green.
    prog_lambert.setGeometryColor(glm::vec4(0,1,0,1));



    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
//    vao.bind();
    glBindVertexArray(vao);

}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    gl_camera = Camera(w, h);
    glm::mat4 viewproj = gl_camera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    prog_lambert.setViewProjMatrix(viewproj);
    prog_flat.setViewProjMatrix(viewproj);
    prog_skeleton.setViewProjMatrix(viewproj);
    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
//DO NOT CONSTRUCT YOUR SCENE GRAPH IN THIS FUNCTION!
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog_flat.setViewProjMatrix(gl_camera.getViewProj());
    prog_lambert.setViewProjMatrix(gl_camera.getViewProj());
    prog_skeleton.setViewProjMatrix(gl_camera.getViewProj());
    //geom_mesh.create();


    //geom_spoint.create();
    //geom_sline.create();
    //geom_sface.create();
#define NOPE
#ifdef NOPE
    //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
    //Note that we have to transpose the model matrix before passing it to the shader
    //This is because OpenGL expects column-major matrices, but you've
    //implemented row-major matrices.
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(3,3,3));
    //Send the geometry's transformation matrix to the shader
    //prog_lambert.setModelMatrix(model);
    //Draw the example sphere using our lambert shader
    //prog_lambert.draw(geom_sphere);

    //Now do the same to render the cylinder
    //We've rotated it -45 degrees on the Z axis, then translated it to the point <2,2,0>
    //model = glm::translate(glm::mat4(1.0f), glm::vec3(2,2,0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0,0,1));
    //prog_lambert.setModelMatrix(model);
    //prog_lambert.draw(geom_cylinder);


    //model = glm::translate(glm::mat4(2.0f), glm::vec3(2,2,0)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(3,3,3));
    prog_lambert.setModelMatrix(model);
    prog_skeleton.setModelMatrix(model);
    if(shaderMode==0)
        prog_lambert.draw(geom_mesh);
    if(shaderMode==1)
    {
        //geom_mesh.create();
        updateTransformations();
        prog_skeleton.draw(geom_mesh);
    }

    glDisable(GL_DEPTH_TEST);
    prog_flat.setModelMatrix(model);
    prog_flat.draw(geom_spoint);

    prog_flat.setModelMatrix(model);
    prog_flat.draw(geom_sline);
    prog_flat.draw(geom_sface);


    //model = glm::translate(glm::mat4(1.0f), glm::vec3(2,2,0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(3,3,1));
    //prog_flat.setModelMatrix(model);
    //prog_flat.draw(geom_spoint);
    if(rootjoint!=nullptr)
    DrawJoint(rootjoint);
    glEnable(GL_DEPTH_TEST);
#endif
}


void MyGL::keyPressEvent(QKeyEvent *e)
{

    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used, but I really dislike their
    // syntax so I chose to be lazy and use a long
    // chain of if statements instead
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    } else if (e->key() == Qt::Key_Right) {
        gl_camera.RotateAboutUp(-amount);
    } else if (e->key() == Qt::Key_Left) {
        gl_camera.RotateAboutUp(amount);
    } else if (e->key() == Qt::Key_Up) {
        gl_camera.RotateAboutRight(-amount);
    } else if (e->key() == Qt::Key_Down) {
        gl_camera.RotateAboutRight(amount);
    } else if (e->key() == Qt::Key_1) {
        gl_camera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        gl_camera.fovy -= amount;
    } else if (e->key() == Qt::Key_W) {
        gl_camera.TranslateAlongLook(amount);
    } else if (e->key() == Qt::Key_S) {
        gl_camera.TranslateAlongLook(-amount);
    } else if (e->key() == Qt::Key_D) {
        gl_camera.TranslateAlongRight(amount);
    } else if (e->key() == Qt::Key_A) {
        gl_camera.TranslateAlongRight(-amount);
    } else if (e->key() == Qt::Key_Q) {
        gl_camera.TranslateAlongUp(-amount);
    } else if (e->key() == Qt::Key_E) {
        gl_camera.TranslateAlongUp(amount);
    } else if (e->key() == Qt::Key_R) {
        gl_camera = Camera(this->width(), this->height());
        renderMode=abs(renderMode-1);
    }else if(e->key()==Qt::Key_P){
        shaderMode=abs(shaderMode-1);
    }
    //add by Xi Yang
    else if(e->key()==Qt::Key_N){
//        emit sig_KeyPressN();
        drawAndSelectNextEdge();
    }else if(e->key()==Qt::Key_M){
//        emit sig_KeyPressM();
        drawAndSelectSymEdge();
    }else if(e->key()==Qt::Key_F){
        emit sig_KeyPressF();
    }else if(e->key()==Qt::Key_V){
        emit sig_KeyPressV();
    }//else if(e->key()==Qt::Key_H){
     //   emit sig_KeyPressH();
    //}else if((e->key()==Qt::Key_H)&& Qt::ShiftModifier){
    //    std::cout<<"hello"<<std::endl;
    //    emit sig_KeyPressShiftH();
    //}
    else if(e->key()==Qt::Key_H)
    {
        if(e->modifiers()== Qt::ShiftModifier)
            emit sig_KeyPressShiftH();
        else
            emit sig_KeyPressH();
    }



    gl_camera.RecomputeAttributes();
    update();  // Calls paintGL, among other things
}

void MyGL::timerUpdate()
{
    // This function is called roughly 60 times per second.
    // Use it to perform any repeated actions you want to do,
    // such as
    timeCount++;
    prog_lambert.setUnifTime(timeCount);
    prog_lambert.SetUnifRenderMode(renderMode);
    update();
}

void MyGL::slot_VertexHighlight(QListWidgetItem *p)
{
    int n=p->text().toInt();
    Vertex* v=geom_mesh.GetVertexByNum(n);
    geom_spoint.SetPointPos(v);
    emit sig_VertexX(v);
    emit sig_VertexY(v);
    emit sig_VertexZ(v);
    update();

}
void MyGL::slot_EdgeHighlight(QListWidgetItem *p)
{
    int n=p->text().toInt();
    HalfEdge* h=geom_mesh.GetEdgeByNum(n);
    selected_he = h;
    geom_sline.SetHE(h);
    update();
}

void MyGL::slot_FaceHighlight(QListWidgetItem *p)
{
    int n=p->text().toInt();
    Face* f=geom_mesh.GetFaceByNum(n);
    geom_sface.SetsFace(f);
    emit sig_FaceR(f);
    emit sig_FaceG(f);
    emit sig_FaceB(f);
    update();
}

void MyGL::slot_VertexXChanged(QListWidgetItem *p,double x)
{

    int n=p->text().toInt();
    Vertex* v=geom_mesh.GetVertexByNum(n);
    glm::vec3 pos=v->GetPos();
    pos[0]=x;
    v->SetPos(pos);
    geom_mesh.create();
    geom_spoint.SetPointPos(v);
    geom_sline.create();
    geom_sface.create();
    update();
}
void MyGL::slot_VertexYChanged(QListWidgetItem *p,double x)
{
    int n=p->text().toInt();
    Vertex* v=geom_mesh.GetVertexByNum(n);
    glm::vec3 pos=v->GetPos();
    pos[1]=x;
    v->SetPos(pos);
    geom_mesh.create();
    geom_spoint.SetPointPos(v);
    geom_sline.create();
    geom_sface.create();
    update();
}
void MyGL::slot_VertexZChanged(QListWidgetItem *p,double x)
{

    int n=p->text().toInt();
    Vertex* v=geom_mesh.GetVertexByNum(n);
    glm::vec3 pos=v->GetPos();
    pos[2]=x;
    v->SetPos(pos);
    geom_mesh.create();
    geom_spoint.SetPointPos(v);
    geom_sline.create();
    geom_sface.create();
    update();
}

void MyGL::slot_FaceRChanged(QListWidgetItem *p, double x)
{
    int n=p->text().toInt();
    Face* f=geom_mesh.GetFaceByNum(n);
    glm::vec4 c=f->GetColor();
    c[0]=x;
    f->SetColor(c);
    geom_mesh.create();
    geom_sface.SetsFace(f);
    update();
}
void MyGL::slot_FaceGChanged(QListWidgetItem *p, double x)
{
    int n=p->text().toInt();
    Face* f=geom_mesh.GetFaceByNum(n);
    glm::vec4 c=f->GetColor();
    c[1]=x;
    f->SetColor(c);
    geom_mesh.create();
    geom_sface.SetsFace(f);
    update();
}
void MyGL::slot_FaceBChanged(QListWidgetItem *p, double x)
{
    int n=p->text().toInt();
    Face* f=geom_mesh.GetFaceByNum(n);
    glm::vec4 c=f->GetColor();
    c[2]=x;
    f->SetColor(c);
    geom_mesh.create();
    geom_sface.SetsFace(f);
    update();
}

void MyGL::drawAndSelectNextEdge()
{
    selected_he = selected_he->GetNext();
    geom_sline.SetHE(selected_he);
    update();
}

void MyGL::drawAndSelectSymEdge()
{
    selected_he = selected_he->GetSym();
    geom_sline.SetHE(selected_he);
    update();
}

void MyGL::slot_DrawNext(QListWidgetItem *p)
{
    int n=p->text().toInt();
    HalfEdge *h=geom_mesh.GetEdgeByNum(n);
    h=h->GetNext();
    geom_sline.SetHE(h);
    update();

}
void MyGL::slot_DrawSym(QListWidgetItem *p)
{
    int n=p->text().toInt();
    HalfEdge *h=geom_mesh.GetEdgeByNum(n);
    h=h->GetSym();
    geom_sline.SetHE(h);
    update();
}

void MyGL::slot_DrawFace(QListWidgetItem *p)
{
    int n=p->text().toInt();
    HalfEdge *h=geom_mesh.GetEdgeByNum(n);
    geom_sface.SetsFace(h->GetFace());
    update();
}
void MyGL::slot_DrawVertex(QListWidgetItem *p)
{
    int n=p->text().toInt();
    HalfEdge *h=geom_mesh.GetEdgeByNum(n);
    geom_spoint.SetPointPos(h->GetVertex());
    update();
}
void MyGL::slot_DrawHalfEdge(QListWidgetItem *p)
{
    int n=p->text().toInt();
    Vertex* v=geom_mesh.GetVertexByNum(n);
    geom_sline.SetHE(v->GetEdge());
    update();
}
void MyGL::slot_DrawFaceHE(QListWidgetItem *p)
{

    int n=p->text().toInt();
    Face* f=geom_mesh.GetFaceByNum(n);
    geom_sline.SetHE(f->GetStartEdge());
    update();
}

void MyGL::LoadObj(std::vector<glm::vec3> vert_pos, std::vector<glm::vec2> vert_vt, std::vector<glm::vec3> vert_nor, std::vector<std::vector<glm::vec3> > faceVector)
{
    geom_mesh.CreateFromOBJ(vert_pos,vert_vt,vert_nor,faceVector);
    geom_mesh.create();
    emit sig_VertexItem(geom_mesh.GetVertexNum());
    emit sig_FaceItem(geom_mesh.GetFaceNum());
    emit sig_HEItem(geom_mesh.GetEgdeNum());
    update();
}

void MyGL::slot_AddVertex(QListWidgetItem *p)
{
    if(p==nullptr)
    {
        std::cout<<"please select a halfedge!!!!!!!!!"<<std::endl;
        return;
    }
    int n=p->text().toInt();
    HalfEdge *h=geom_mesh.GetEdgeByNum(n);
    HalfEdge *h2=h->GetSym();
    glm::vec3 v,v2;
    v=h->GetVertex()->GetPos();
    v2=h2->GetVertex()->GetPos();
    glm::vec3 pos=(v+v2);
    pos[0]=pos[0]*0.5;
    pos[1]=pos[1]*0.5;
    pos[2]=pos[2]*0.5;
    geom_mesh.AddVertex(h,pos);
    geom_mesh.create();
    emit sig_VertexItem(geom_mesh.GetVertexNum());
    emit sig_FaceItem(geom_mesh.GetFaceNum());
    emit sig_HEItem(geom_mesh.GetEgdeNum());
    geom_sline.create();
    update();
}

void MyGL::slot_TriangulateFace(QListWidgetItem *p)
{
    if(p==nullptr)
    {
        std::cout<<"please select a face!!!!!!!!!"<<std::endl;
        return;
    }
    int n=p->text().toInt();
    Face* f=geom_mesh.GetFaceByNum(n);
    geom_mesh.Triangulate(f);
    geom_mesh.create();
    emit sig_VertexItem(geom_mesh.GetVertexNum());
    emit sig_FaceItem(geom_mesh.GetFaceNum());
    emit sig_HEItem(geom_mesh.GetEgdeNum());
    geom_sface.create();
    update();
}

void MyGL::slot_Subdivision()
{
    std::vector<glm::vec3> cent=geom_mesh.CalculateCentroid();
    std::vector<glm::vec3> eg=geom_mesh.CalculateEdgeVertex(cent);
    geom_mesh.SmoothVertex(cent,eg);
    geom_mesh.Subdivision(cent,eg);
    geom_mesh.create();
    emit sig_VertexItem(geom_mesh.GetVertexNum());
    emit sig_FaceItem(geom_mesh.GetFaceNum());
    emit sig_HEItem(geom_mesh.GetEgdeNum());
    update();
}
void MyGL::slot_ExtrudeFace(QListWidgetItem *p)
{
    if(p==nullptr)
    {
        std::cout<<"please select a face!!!!!!!!!"<<std::endl;
        return;
    }
    int n=p->text().toInt();
    Face* f=geom_mesh.GetFaceByNum(n);
    geom_mesh.Extrude(f);
    geom_mesh.create();
    emit sig_VertexItem(geom_mesh.GetVertexNum());
    emit sig_FaceItem(geom_mesh.GetFaceNum());
    emit sig_HEItem(geom_mesh.GetEgdeNum());
    geom_sface.create();
    update();

}

Joint* MyGL::CreateFromJson(QJsonObject obj)
{

   QString name = obj["name"].toString();
   Joint* nj= new Joint(name);
   QJsonArray pos = obj["pos"].toArray();
   glm::vec3 p(pos[0].toDouble(),pos[1].toDouble(),pos[2].toDouble());
   nj->SetPosition(p);
   //std::cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<std::endl;
   QJsonArray rot = obj["rot"].toArray();
   float angle=rot[0].toDouble();
   glm::quat q;
//   if(fabs(angle)<1e-6)
//   {
//       q.w=0.0f;
//       q.x=1.0f;
//       q.y=0.0f;
//       q.z=0.0f;
//   }
   //else{
   q.w=cos(angle/2);
   q.x=rot[1].toDouble()*sin(angle/2);
   q.y=rot[2].toDouble()*sin(angle/2);
   q.z=rot[3].toDouble()*sin(angle/2);
   //}
   //std::cout<<"q=  "<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<std::endl;
   nj->SetRotation(q);
   QJsonArray child = obj["children"].toArray();
   for(int j=0;j<child.size();j++)
   {
       QJsonObject cd=child[j].toObject();
       Joint *cdp=CreateFromJson(cd);
       nj->addChild(cdp);
   }
   //glm::mat4 bm=nj->GetOverallTransformation();
   //nj->SetBindMatrix(glm::inverse(bm));
   //nj->SetBindMatrix(glm::mat4(1.0f)/bm);
   geom_mesh.AddInfluenceJoint(nj);
   return nj;
}
void MyGL::SetRootJoint(Joint *p)
{
    emit sig_SendJoint(p);
    rootjoint=p;
    for(unsigned int i=0;i<geom_mesh.GetJointsNum();i++)
    {
        Joint* ji=geom_mesh.GetJointByNum(i);
        glm::mat4 overall=ji->GetOverallTransformation();
        ji->SetBindMatrix(glm::inverse(overall));
    }
    //geom_mesh.SetInfluenceJoints(rootjoint);
    //DrawJoint(rootjoint);


    update();


    //std::cout<<p->GetJointName().toStdString()<<std::endl;
}
void MyGL::DrawJoint(Joint* j)
{

    if(j==nullptr)
        return;
    if(j==selected_joint)
        geom_Jsphere.SetJoint(j,glm::vec4(0,1,0,1));
    else
    geom_Jsphere.SetJoint(j);
    //geom_Jsphere.create();

    //geom_Jline.create();
    //glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(3,3,3));
    //prog_flat.setModelMatrix(model);
    if(j->GetParents()!=nullptr)
    {
        geom_Jline.SetLJoint(j);

        prog_flat.draw(geom_Jline);
    }
    prog_flat.draw(geom_Jsphere);
    for(unsigned int i=0;i<j->GetChildren().size();i++)
    {
        DrawJoint(j->GetChildrenByNum(i));
    }

    for(unsigned int i=0;i<j->GetChildren().size();i++)
    {
        DrawJoint(j->GetChildrenByNum(i));
    }
}
void MyGL::slot_Skinning()
{

    //geom_mesh.SetInfluenceJoints(rootjoint);
    geom_mesh.skinningfunction();
    updateBindMatrices();
    updateTransformations();
    geom_mesh.create();

    shaderMode=1;
    QMessageBox::information(NULL, QString("Info"), QString("Skinning Complete"));
    update();

}

void MyGL::slot_JointClicked(QTreeWidgetItem *n, int i)
{

    Joint *p=(Joint*)n;
    selected_joint=p;
    emit sig_ShowLocalTrans(p);
    emit sig_ShowRotation(p);
    emit sig_JointPosX(p->GetPosition()[0]);
    emit sig_JointPosY(p->GetPosition()[1]);
    emit sig_JointPosZ(p->GetPosition()[2]);
//    emit sig_JointRotW(p->GetRotation().w);
//    emit sig_JointRotX(p->GetRotation().x);
//    emit sig_JointRotY(p->GetRotation().y);
//    emit sig_JointRotZ(p->GetRotation().z);

}
void MyGL::slot_JointPosXChanged(double x)
{
    glm::vec3 pos=selected_joint->GetPosition();
    pos[0]=x;
    selected_joint->SetPosition(pos);
    emit sig_ShowLocalTrans(selected_joint);
    updateTransformations();
    update();
}
void MyGL::slot_JointPosYChanged(double x)
{
    glm::vec3 pos=selected_joint->GetPosition();
    pos[1]=x;
    selected_joint->SetPosition(pos);
    emit sig_ShowLocalTrans(selected_joint);
    updateTransformations();
    update();
}
void MyGL::slot_JointPosZChanged(double x)
{
    glm::vec3 pos=selected_joint->GetPosition();
    pos[2]=x;
    selected_joint->SetPosition(pos);
    emit sig_ShowLocalTrans(selected_joint);
    updateTransformations();
    update();
}
//void MyGL::slot_JointRotWChanged(double x)
//{
//    glm::quat qua=selected_joint->GetRotation();
//    qua[0]=x;
//    selected_joint->SetRotation(qua);
//    update();
//}
//void MyGL::slot_JointRotXChanged(double x)
//{
//    glm::quat qua=selected_joint->GetRotation();
//    qua[1]=x;
//    selected_joint->SetRotation(qua);
//    update();
//}
//void MyGL::slot_JointRotYChanged(double x)
//{
//    glm::quat qua=selected_joint->GetRotation();
//    qua[2]=x;
//    selected_joint->SetRotation(qua);
//    update();
//}
//void MyGL::slot_JointRotZChanged(double x)
//{
//    glm::quat qua=selected_joint->GetRotation();
//    qua[3]=x;
//    selected_joint->SetRotation(qua);
//    update();
//}
void MyGL::slot_RotateX_1()
{
    float angle=glm::radians(5.0/2);
    glm::quat q;
    q.w=cos(angle);
    q.x=sin(angle);
    q.y=0;
    q.z=0;
    if(selected_joint!=nullptr)
    {
        selected_joint->RotateByQuat(q);
        emit sig_ShowLocalTrans(selected_joint);
        emit sig_ShowRotation(selected_joint);
//        emit sig_JointPosX(selected_joint->GetPosition()[0]);
//        emit sig_JointPosY(selected_joint->GetPosition()[1]);
//        emit sig_JointPosZ(selected_joint->GetPosition()[2]);
//        emit sig_JointRotW(selected_joint->GetRotation().w);
//        emit sig_JointRotX(selected_joint->GetRotation().x);
//        emit sig_JointRotY(selected_joint->GetRotation().y);
//        emit sig_JointRotZ(selected_joint->GetRotation().z);
    }
    updateTransformations();
    update();
}
void MyGL::slot_RotateX_2()
{
    float angle=glm::radians(-5.0/2);
    glm::quat q;
    q.w=cos(angle);
    q.x=sin(angle);
    q.y=0.0;
    q.z=0.0;
    if(selected_joint!=nullptr)
    {
        selected_joint->RotateByQuat(q);
        emit sig_ShowLocalTrans(selected_joint);
        emit sig_ShowRotation(selected_joint);
//        emit sig_JointPosX(selected_joint->GetPosition()[0]);
//        emit sig_JointPosY(selected_joint->GetPosition()[1]);
//        emit sig_JointPosZ(selected_joint->GetPosition()[2]);
//        emit sig_JointRotW(selected_joint->GetRotation().w);
//        emit sig_JointRotX(selected_joint->GetRotation().x);
//        emit sig_JointRotY(selected_joint->GetRotation().y);
//        emit sig_JointRotZ(selected_joint->GetRotation().z);
    }
    updateTransformations();
    update();
}
void MyGL::slot_RotateY()
{
    float angle=glm::radians(5.0/2);
    glm::quat q;
    q.w=cos(angle);
    q.x=0.0;
    q.y=sin(angle);
    q.z=0.0;
    if(selected_joint!=nullptr)
    {
        selected_joint->RotateByQuat(q);
        emit sig_ShowLocalTrans(selected_joint);
        emit sig_ShowRotation(selected_joint);
//        emit sig_JointRotW(selected_joint->GetRotation().w);
//        emit sig_JointRotX(selected_joint->GetRotation().x);
//        emit sig_JointRotY(selected_joint->GetRotation().y);
//        emit sig_JointRotZ(selected_joint->GetRotation().z);
    }
    updateTransformations();
    update();
}
void MyGL::slot_RotateY_()
{
    float angle=glm::radians(-5.0/2);
    glm::quat q;
    q.w=cos(angle);
    q.x=0.0;
    q.y=sin(angle);
    q.z=0.0;
    if(selected_joint!=nullptr)
    {
        selected_joint->RotateByQuat(q);
        emit sig_ShowRotation(selected_joint);
        emit sig_ShowLocalTrans(selected_joint);
//        emit sig_JointRotW(selected_joint->GetRotation().w);
//        emit sig_JointRotX(selected_joint->GetRotation().x);
//        emit sig_JointRotY(selected_joint->GetRotation().y);
//        emit sig_JointRotZ(selected_joint->GetRotation().z);
    }
    updateTransformations();
    update();
}
void MyGL::slot_RotateZ()
{
    float angle=glm::radians(5.0/2);
    glm::quat q;
    q.w=cos(angle);
    q.x=0.0;
    q.y=0.0;
    q.z=sin(angle);
    if(selected_joint!=nullptr)
    {
        selected_joint->RotateByQuat(q);
        emit sig_ShowRotation(selected_joint);
        emit sig_ShowLocalTrans(selected_joint);
//        emit sig_JointRotW(selected_joint->GetRotation().w);
//        emit sig_JointRotX(selected_joint->GetRotation().x);
//        emit sig_JointRotY(selected_joint->GetRotation().y);
//        emit sig_JointRotZ(selected_joint->GetRotation().z);
    }
    updateTransformations();
    update();
}
void MyGL::slot_RotateZ_()
{
    float angle=glm::radians(-5.0/2);
    glm::quat q;
    q.w=cos(angle);
    q.x=0.0;
    q.y=0.0;
    q.z=sin(angle);
    if(selected_joint!=nullptr)
    {
        selected_joint->RotateByQuat(q);
        emit sig_ShowRotation(selected_joint);
        emit sig_ShowLocalTrans(selected_joint);
//        emit sig_JointRotW(selected_joint->GetRotation().w);
//        emit sig_JointRotX(selected_joint->GetRotation().x);
//        emit sig_JointRotY(selected_joint->GetRotation().y);
//        emit sig_JointRotZ(selected_joint->GetRotation().z);
    }
    updateTransformations();
    update();
}
void MyGL::updateBindMatrices()
{
    if(rootjoint==nullptr)
        return;
    std::vector<Joint*> jts;
    rootjoint->GetJointList(rootjoint,jts);
    glm::mat4 bindMs[100];
    unsigned int jtNum=geom_mesh.GetJointsNum();
    for(unsigned int i=0;i<100;i++)
    {
        bindMs[i]=glm::mat4(1.0f);
    }
    for(unsigned int i=0;i<jtNum;i++)
    {
        bindMs[i]=geom_mesh.GetJointByNum(i)->GetBindMatrix();
    }
    prog_skeleton.SetUnifBindMatrices(bindMs);

}
void MyGL::updateTransformations()
{
    if(rootjoint==nullptr)
        return;
    glm::mat4 Trans[100];
    unsigned int jtNum=geom_mesh.GetJointsNum();
    for(unsigned int i=0;i<100;i++)
    {
        Trans[i]=glm::mat4(1.0f);
    }
    for(unsigned int i=0;i<jtNum;i++)
    {
        Trans[i]=geom_mesh.GetJointByNum(i)->GetOverallTransformation();

    }
    prog_skeleton.SetUnifJointTransformations(Trans);

}

void MyGL::clearmeshjoints()
{
    geom_mesh.clearjoints();
}
