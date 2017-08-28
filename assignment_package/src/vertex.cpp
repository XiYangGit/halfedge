#include "vertex.h"
#include <iostream>
///by Xi Yang
///--------------------------------------------
/// ----------implements of Vertex-------------
/// -------------------------------------------
Vertex::Vertex():Vertex(glm::vec3(1.0f),nullptr,0){}
Vertex::Vertex(glm::vec3 v,HalfEdge* e,unsigned int id):
    pos(v),edge(e),VertexID(id),jointsID(glm::ivec2(0,0)),weights(glm::vec2(0,0))
{

}
Vertex::~Vertex()
{
    edge=nullptr;
}
void Vertex::SetPos(glm::vec3 v)
{
    pos=v;
}
void Vertex::SetEdge(HalfEdge *e)
{
    edge=e;
}
void Vertex::SetVertexID(unsigned int i)
{
    VertexID=i;
}

glm::vec3 Vertex::GetPos()
{
    return pos;
}
HalfEdge* Vertex::GetEdge()
{
    return edge;
}
unsigned int Vertex::GetVertexID()
{
    return VertexID;
}


//void Vertex::SetJoints(Joint *root)
//{
//    if(root!=nullptr)
//    {
//        std::vector<Joint*> tempJoints;
//        root->GetJointList(root,tempJoints);
//        //std::cout<<"joint size "<<tempJoints.size()<<std::endl;
//        std::vector<float> tempDist;
//        for(unsigned int i=0;i<tempJoints.size();i++)
//        {
//            glm::vec4 posi=tempJoints[i]->GetOverallTransformation()*glm::vec4(0,0,0,1);
//            //float dist_2=pow(pos[0]-posi[0],2)+pow(pos[1]-posi[1],2)+(pos[2]-posi[2],2);
//            float dist_2=glm::length(posi-glm::vec4(pos,1));
//            tempDist.push_back(dist_2);
//        }
//        unsigned int min1=0;
//        unsigned int min2=0;
//        for(unsigned int i=0;i<tempJoints.size();i++)
//        {
//            if(tempDist[i]<tempDist[min1])
//                min1=i;
//        }
//        tempDist[min1]=tempDist[min1]+1e007;
//        for(unsigned int i=0;i<tempJoints.size();i++)
//        {
//            if(tempDist[i]<tempDist[min2])
//                min2=i;
//        }
//        joints.push_back(tempJoints[min1]);
//        joints.push_back(tempJoints[min2]);
//        jointsID.push_back(min1);
//        jointsID.push_back(min2);
//        //std::cout<<"joint id "<<min1<<" "<<min2<<std::endl;

//    }
//}


glm::ivec2 Vertex::GetJointIDs()
{

    return jointsID;
}
glm::vec2 Vertex::GetWeights()
{
    return weights;
}

void Vertex::SetJointIDs(glm::ivec2 j)
{
    jointsID=j;
}
void Vertex::SetWeights(glm::vec2 w)
{
    weights=w;
}
