#include "sface.h"
#include<la.h>
#include <iostream>

sFace::sFace(GLWidget277 *context):Drawable(context),fc(nullptr)
{

}

void sFace::SetsFace(Face *f)
{
    fc=f;
    destroy();
    create();
}

void sFace::create()
{

    int ptNum=0;
    glm::vec4 c(1.0f);
    std::vector<glm::vec4> pos;
    if(fc!=nullptr)
    {

        c=fc->GetColor();
        c=glm::vec4(1,1,1,2)-c;
        HalfEdge *h=fc->GetStartEdge();
        pos.push_back(glm::vec4(h->GetVertex()->GetPos(),1));
        ptNum+=1;
        h=h->GetNext();
        while(h!=fc->GetStartEdge())
        {

            pos.push_back(glm::vec4(h->GetVertex()->GetPos(),1));
            h=h->GetNext();
            ptNum+=1;
        }

    }

//    GLuint pt_idx[2*ptNum];
//    glm::vec4 pt_vert_pos[ptNum];
//    glm::vec4 pt_vert_col[ptNum];
//    for(int i=0;i<ptNum;i++)
//    {
//        pt_vert_pos[i]=pos[i];
//        pt_vert_col[i]=c;
//        pt_idx[2*i]=i;
//        if(i==ptNum-1)
//            pt_idx[2*i+1]=0;
//        else
//            pt_idx[2*i+1]=i+1;

//    }
    std::vector<GLuint> pt_idx;
    std::vector<glm::vec4> pt_vert_pos;
    std::vector<glm::vec4> pt_vert_col;
    for(int i=0;i<ptNum;i++)
    {
        pt_vert_pos.push_back(pos[i]);
        pt_vert_col.push_back(c);
        pt_idx.push_back(i);
        if(i==ptNum-1)
            pt_idx.push_back(0);
        else
            pt_idx.push_back(i+1);

    }

    count = 2*ptNum;


    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2*ptNum * sizeof(GLuint), pt_idx.data(), GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, ptNum * sizeof(glm::vec4), pt_vert_pos.data(), GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER, ptNum * sizeof(glm::vec4), pt_vert_col.data(), GL_STATIC_DRAW);

}






GLenum sFace::drawMode()
{
    return GL_LINES;
}
