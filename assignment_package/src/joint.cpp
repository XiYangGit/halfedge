#include "joint.h"
#include <iostream>

Joint::Joint()
{

}
Joint::Joint(const QString &name):Name(name),Parents(nullptr),children(),
    Position(glm::vec3(0.0f)),Rotation(glm::quat(0, 1, 0, 0)),
    BindMatrix(glm::mat4(1.0f))
{
    setText(0,name);
}
Joint::~Joint()
{

    while(children.size()>0)
    {
        delete children[0];
        children.erase(children.begin());
    }
    children.clear();
}
void Joint::addChild(QTreeWidgetItem *c)
{
    QTreeWidgetItem::addChild(c);
    children.push_back((Joint*)c);
    ((Joint*)c)->SetParents(this);
}

Joint* Joint::GetParents()
{
    return Parents;
}
std::vector<Joint*> Joint::GetChildren()
{
    return children;
}
glm::vec3 Joint::GetPosition()
{
    return Position;
}
glm::quat Joint::GetRotation()
{
    return Rotation;
}
glm::mat4 Joint::GetBindMatrix()
{
    return BindMatrix;
}
QString Joint::GetJointName()
{
    return Name;
}
void Joint::SetParents(Joint *p)
{
    Parents=p;
}
void Joint::SetPosition(glm::vec3 pos)
{
    Position=pos;
}
void Joint::SetRotation(glm::quat rot)
{
    Rotation=rot;
}
void Joint::SetBindMatrix(glm::mat4 bm)
{
    BindMatrix=bm;
}
glm::mat4 Joint::GetLocalTransformation()
{
    glm::mat4 localtrans;
    float w=Rotation.w;
    float x=Rotation.x;
    float y=Rotation.y;
    float z=Rotation.z;
    localtrans[0][0]=pow(w,2)+pow(x,2)-pow(y,2)-pow(z,2);
    localtrans[0][1]=2*x*y-2*w*z;
    localtrans[0][2]=2*x*z+2*w*y;
    localtrans[0][3]=Position[0];
    localtrans[1][0]=2*x*y+2*w*z;
    localtrans[1][1]=pow(w,2)-pow(x,2)+pow(y,2)-pow(z,2);
    localtrans[1][2]=2*y*z-2*w*x;
    localtrans[1][3]=Position[1];
    localtrans[2][0]=2*x*z-2*w*y;
    localtrans[2][1]=2*y*z+2*w*x;
    localtrans[2][2]=pow(w,2)-pow(x,2)-pow(y,2)+pow(z,2);
    localtrans[2][3]=Position[2];
    localtrans[3][0]=0.0f;
    localtrans[3][1]=0.0f;
    localtrans[3][2]=0.0f;
    localtrans[3][3]=1.0f;

//        localtrans[0][0]=1-2*pow(y,2)-2*pow(z,2);
//        localtrans[0][1]=2*x*y-2*w*z;
//        localtrans[0][2]=2*x*z+2*w*y;
//        localtrans[1][0]=2*x*y+2*w*z;
//        localtrans[1][1]=1-2*pow(x,2)-2*pow(z,2);
//        localtrans[1][2]=2*y*z-2*w*x;
//        localtrans[2][0]=2*x*z-2*w*y;
//        localtrans[2][1]=2*y*z+2*w*x;
//        localtrans[2][2]=1-2*pow(x,2)-2*pow(y,2);
//        localtrans[3][0]=0.0f;
//        localtrans[3][1]=0.0f;
//        localtrans[3][2]=0.0f;
//        localtrans[3][3]=1.0f;
//    localtrans[0][3]=Position[0];
//    localtrans[1][3]=Position[1];
//    localtrans[2][3]=Position[2];

    return glm::transpose(localtrans);
}
glm::mat4 Joint::GetOverallTransformation()
{
//    glm::mat4 overalltrans=glm::mat4(1.0f);
//    overalltrans=this->GetLocalTransformation();
//    Joint *p=Parents;
//    while(p!=nullptr)
//    {
//        overalltrans=p->GetLocalTransformation()*overalltrans;
//        p=p->GetParents();

//    }
    glm::mat4 overalltrans;
    if(Parents!=nullptr)
    {
        overalltrans=Parents->GetOverallTransformation()*this->GetLocalTransformation();
    }
    else
        overalltrans=this->GetLocalTransformation();
    return overalltrans;
}
Joint* Joint::GetChildrenByNum(unsigned int n)
{
    if(n<children.size())
        return children[n];
    else
        return nullptr;
}
void Joint::GetJointList(Joint *j, std::vector<Joint *> &jointlist)
{
    jointlist.push_back(j);
    for(unsigned int i=0;i<j->GetChildren().size();i++)
    {
        GetJointList(j->GetChildrenByNum(i),jointlist);
    }
}
void Joint::RotateByQuat(glm::quat q)
{
    Rotation=Rotation*q;
    glm::normalize(Rotation);
}
