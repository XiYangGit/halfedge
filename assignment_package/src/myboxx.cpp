#include "myboxx.h"
#include <iostream>

void MyBoxX::slot_VertexX(Vertex *p)
{
    glm::vec3 pos=p->GetPos();
    setValue(pos[0]);
}
void MyBoxY::slot_VertexY(Vertex *p)
{
    glm::vec3 pos=p->GetPos();
    setValue(pos[1]);
}
void MyBoxZ::slot_VertexZ(Vertex *p)
{
    glm::vec3 pos=p->GetPos();
    setValue(pos[2]);
}
void MyBoxR::slot_FaceR(Face *p)
{
    glm::vec4 c=p->GetColor();
    setValue(c[0]);
}
void MyBoxG::slot_FaceG(Face *p)
{
    glm::vec4 c=p->GetColor();
    setValue(c[1]);
}
void MyBoxB::slot_FaceB(Face *p)
{
    glm::vec4 c=p->GetColor();
    setValue(c[2]);
}
