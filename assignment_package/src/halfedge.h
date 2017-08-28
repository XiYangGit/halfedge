#ifndef HALFEDGE_H
#define HALFEDGE_H
#include <la.h>
#include <glm/glm.hpp>
#include "vertex.h"
#include "face.h"
class Vertex;
class Face;
class HalfEdge
{
private:
    Face* face;
    Vertex* vert;
    HalfEdge* next;
    HalfEdge* sym;
    unsigned int HalfEdgeID;
public:
    HalfEdge();
    HalfEdge(Face*,Vertex*,HalfEdge*,HalfEdge*,unsigned int);
    ~HalfEdge();
    void SetFace(Face*);
    void SetVertex(Vertex*);
    void SetNext(HalfEdge*);
    void SetSym(HalfEdge*);
    void SetHalfEdgeID(unsigned int);
    Face* GetFace();
    Vertex* GetVertex();
    HalfEdge* GetNext();
    HalfEdge* GetSym();
    unsigned int GetHalfEdgeID();
    HalfEdge* GetPrevious();


};

#endif // HALFEDGE_H
