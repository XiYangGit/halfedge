#include "jsphere.h"
#include <la.h>
#include <iostream>
static const int JS_IDX_COUNT = 72;
static const int JS_VERT_COUNT = 36;

JSphere::JSphere(GLWidget277 *context):Drawable(context),jt(nullptr),color(glm::vec4(1.0f))
{

}
void JSphere::SetJoint(Joint *j)
{
    jt=j;
    color=glm::vec4(1.0f);
    destroy();
    create();
    //std::cout<<"inside sphere!!!!!!!"<<std::endl;
}
void JSphere::SetJoint(Joint *j, glm::vec4 c)
{
    jt=j;
    color=c;
    destroy();
    create();

}
GLenum JSphere::drawMode()
{
    return GL_LINES;
}
void createJSVertexPositions(glm::vec4 (&JS_vert_pos)[JS_VERT_COUNT])
{

    //Store verts (IDX 0 - 11)
    for(int i = 0; i < 12; i++){
        glm::vec4 v = glm::rotate(glm::mat4(1.0f), glm::radians(i*30.0f), glm::vec3(0, 1, 0)) * glm::vec4(0.5f,0.0f,0.0f,1);
        JS_vert_pos[i] = v;
    }


    //Store verts (IDX 12 - 23)
    for(int i = 12; i < 24; i++){
        glm::vec4 v = glm::rotate(glm::mat4(1.0f), glm::radians((i-12)*30.0f), glm::vec3(1, 0, 0)) * glm::vec4(0.0f,0.0f,0.5f,1);
        JS_vert_pos[i] = v;
    }

    //Store verts (IDX 24 - 35)
    for(int i = 24; i < 36; i++){
        glm::vec4 v = glm::rotate(glm::mat4(1.0f), glm::radians((i-24)*30.0f), glm::vec3(0, 0, 1)) * glm::vec4(0.5f,0.0f,0.0f,1);
        JS_vert_pos[i] = v;
    }
}
void createJSIndices(GLuint (&JS_idx)[JS_IDX_COUNT])
{
    for(int i = 0; i < JS_VERT_COUNT; i++){
        JS_idx[2*i]=i;
        JS_idx[2*i+1]=i+1;
    }
    JS_idx[23]=0;
    JS_idx[47]=12;
    JS_idx[71]=24;

}
void JSphere::create()
{

    GLuint JS_idx[JS_IDX_COUNT];
    glm::vec4 JS_vert_pos[JS_VERT_COUNT];
    glm::vec4 JS_vert_col[JS_VERT_COUNT];
    if(jt!=nullptr)
    {
         glm::mat4 jttrans=jt->GetOverallTransformation();
         createJSVertexPositions(JS_vert_pos);
         createJSIndices(JS_idx);
         for(int i=0;i<JS_VERT_COUNT;i++)
         {
             //JS_vert_pos[i]=JS_vert_pos[i]*jttrans;
             JS_vert_pos[i]=jttrans*JS_vert_pos[i];
             //JS_vert_col[i]=glm::vec4(1.0f);
             //std::cout<<" vert pos  "<<JS_vert_pos[i][0]<<" "<<JS_vert_pos[i][1]<<" "<<JS_vert_pos[i][2]<<std::endl;
             JS_vert_col[i]=color;
         }
//         for(int i=0;i<4;i++)
//         {
//             std::cout<<jttrans[i][0]<<" "<<jttrans[i][1]<<" "<<jttrans[i][2]<<" "<<jttrans[i][3]<<std::endl;

//         }

    }

//    std::vector<GLuint> J_idx;
//    std::vector<glm::vec4> J_vert_pos;
//    std::vector<glm::vec4> J_vert_col;

//    if(jt!=nullptr)
//    {
//        for(int i=0;i<JS_IDX_COUNT;i++)
//        {
//            J_idx.push_back(JS_idx[i]);
//        }
//        for(int i=0;i<JS_VERT_COUNT;i++)
//        {
//            J_vert_pos.push_back(JS_vert_pos[i]);
//            J_vert_col.push_back(glm::vec4(1.0f));
//        }
//    }
//    count=J_idx.size();
    count=JS_IDX_COUNT;


    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, JS_IDX_COUNT * sizeof(GLuint), JS_idx, GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, JS_VERT_COUNT * sizeof(glm::vec4), JS_vert_pos, GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER, JS_VERT_COUNT * sizeof(glm::vec4), JS_vert_col, GL_STATIC_DRAW);




}
