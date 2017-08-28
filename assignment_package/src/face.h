#ifndef FACE_H
#define FACE_H
#include <la.h>
#include <glm/glm.hpp>
#include "halfedge.h"
class HalfEdge;
class Face
{
 private:
    HalfEdge* start_edge;
    glm::vec4 color;
    unsigned int FaceID;
    glm::vec3 normal;
public:
    Face();
    Face(HalfEdge*, glm::vec4,unsigned int,glm::vec3);
    ~Face();
    void SetStartEdge(HalfEdge*);
    void SetColor(glm::vec4);
    void SetFaceID(unsigned int);
    void SetNormal(glm::vec3);
    void SetNormal();
    HalfEdge* GetStartEdge();
    glm::vec4 GetColor();
    glm::vec3 GetNormal();
    unsigned int GetFaceID();
    HalfEdge* GetPreEdge(HalfEdge*);
    int GetEdgeNum();
    std::vector<HalfEdge*> GetEdgeList();

};

#endif // FACE_H
