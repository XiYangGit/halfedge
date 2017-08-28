#include "jline.h"
#include <la.h>
#include <iostream>
JLine::JLine(GLWidget277 *context):Drawable(context),jt(nullptr)
{

}
void JLine::SetLJoint(Joint *j)
{
    jt=j;
    destroy();
    //std::cout<<"inside line!!!!!!!"<<std::endl;
    create();
}

GLenum JLine::drawMode()
{
    return GL_LINES;
}
void JLine::create()
{
    std::vector<GLuint> pt_idx;
    std::vector<glm::vec4> pt_vert_pos;
    std::vector<glm::vec4> pt_vert_col;


    if((jt!=nullptr)&&(jt->GetParents()!=nullptr))
    {
        //pt_vert_pos.push_back(glm::vec4(0,0,0,1)*jt->GetOverallTransformation());
        pt_vert_pos.push_back(jt->GetOverallTransformation()*glm::vec4(0.0,0.0,0.0,1.0));
        //std::cout<<jt->GetJointName().toStdString()<<std::endl;
        //std::cout<<jt->GetParents()->GetJointName().toStdString()<<std::endl;
        //if(jt->GetParents()!=nullptr)
            //pt_vert_pos.push_back(glm::vec4(0,0,0,1)*jt->GetParents()->GetOverallTransformation());
        pt_vert_pos.push_back(jt->GetParents()->GetOverallTransformation()*glm::vec4(0.0,0.0,0.0,1.0));
            pt_idx.push_back(0);
            pt_idx.push_back(1);
            pt_vert_col.push_back(glm::vec4(1.0f,1.0f,0.0f,1.0f));
            pt_vert_col.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));

    }
    //std::cout<<pt_vert_pos[0][0]<<" "<<pt_vert_pos[0][1]<<" "<<pt_vert_pos[0][2]<<" "<<std::endl;
    //std::cout<<pt_vert_pos[1][0]<<" "<<pt_vert_pos[1][1]<<" "<<pt_vert_pos[1][2]<<" "<<std::endl;

    count=pt_idx.size();
    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, pt_idx.size() * sizeof(GLuint), pt_idx.data(), GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, pt_vert_pos.size() * sizeof(glm::vec4), pt_vert_pos.data(), GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER, pt_vert_pos.size() * sizeof(glm::vec4), pt_vert_col.data(), GL_STATIC_DRAW);


}
