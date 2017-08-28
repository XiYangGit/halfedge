#ifndef VERTEX_H
#define VERTEX_H

#include <la.h>
#include <glm/glm.hpp>
#include "halfedge.h"
#include "joint.h"

class HalfEdge;
class Vertex
{
private:

    glm::vec3 pos;
    HalfEdge* edge;
    unsigned int VertexID;
    glm::ivec2 jointsID;
    glm::vec2 weights;
    //glm::vec2 uv;
public:
    Vertex();
    Vertex(glm::vec3, HalfEdge *, unsigned int);

    ~Vertex();
    void SetPos(glm::vec3);
    void SetEdge(HalfEdge*);
    void SetVertexID(unsigned int);
    //void SetUV(glm::vec2);
    glm::vec3 GetPos();
    HalfEdge* GetEdge();
    unsigned int GetVertexID();
    //glm::vec2 GetUV();

    glm::ivec2 GetJointIDs();
    glm::vec2 GetWeights();
    void SetJointIDs(glm::ivec2);
    void SetWeights(glm::vec2);



};

#endif // VERTEX_H
