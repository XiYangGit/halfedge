#include "sline.h"
#include<la.h>
#include <iostream>


sLine::sLine(GLWidget277 *context):Drawable(context),he(nullptr)
{

}
void sLine::SetHE(HalfEdge *h)
{
    he=h;
    create();
}

void sLine::create()
{
    GLuint pt_idx[2];
    glm::vec4 pt_vert_pos[2];
    glm::vec4 pt_vert_col[2];
    pt_idx[0]=0;
    pt_idx[1]=1;

    if(he!=nullptr)
    {

        pt_vert_pos[0]=glm::vec4(he->GetVertex()->GetPos(),1);
        pt_vert_pos[1]=glm::vec4(he->GetSym()->GetVertex()->GetPos(),1);


    }
    pt_vert_col[0]=glm::vec4(1.0f,1.0f,0.0f,1.0f);
    pt_vert_col[1]=glm::vec4(1.0f,0.0f,0.0f,1.0f);



    count = 2;
    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(GLuint), pt_idx, GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), pt_vert_pos, GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), pt_vert_col, GL_STATIC_DRAW);

}
GLenum sLine::drawMode()
{
    return GL_LINES;
}

