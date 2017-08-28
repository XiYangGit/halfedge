#include "spoint.h"
#include<la.h>
#include <iostream>

sPoint::sPoint(GLWidget277 *context):Drawable(context),vert(nullptr)
{

}
void sPoint::SetPointPos(Vertex *v)
{
    vert=v;
    create();
}

void sPoint::create()
{
    GLuint pt_idx[1];
    glm::vec4 pt_vert_pos[1];
    glm::vec4 pt_vert_col[1];

    pt_idx[0]=0;
    if(vert!=nullptr)
    {
        pt_vert_pos[0]=glm::vec4(vert->GetPos(),1);
    }

    pt_vert_col[0]=glm::vec4(1.0f,1.0f,1.0f,1.0f);

    count = 1;


    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1 * sizeof(GLuint), pt_idx, GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec4), pt_vert_pos, GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec4), pt_vert_col, GL_STATIC_DRAW);


}
GLenum sPoint::drawMode()
{
    return GL_POINTS;
}
